#-
# Copyright (c) 2012-2017 Robert N. M. Watson
# All rights reserved.
#
# This software was developed by SRI International and the University of
# Cambridge Computer Laboratory under DARPA/AFRL contract (FA8750-10-C-0237)
# ("CTSRD"), as part of the DARPA CRASH research programme.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#

#include <cheri/cherireg.h>
#define _CHERI_INTERNAL
#include <machine/cheriasm.h>

#.set mips64
.set noreorder
#.set nobopt
.set noat

#
# Assembly wrapper for CCall on an object-capability.  Its function is to save
# and restore any general-purpose and capability registers needed on either
# side of CCall, but not handled by the compiler.  This is done by creating an
# on-stack frame which will be pointed to by $idc before CCall, and then
# unwrapping it again.  We rely on the compiler and CCall to sort out clearing
# of registers that require it, since they have the information to do so.
#
# Calling conventions into libcheri_invoke:
#
# Registers	Description
# $c0		MIPS address space
# $c1, $c2	Invoked capabilities
# $c3..$c10	Argument capabilities
# $c11..$c16	Caller-save capabilities
# $c17..$c26	Callee-save capabilities
#
# Calling conventions implemented by CCall:
#
# $c1		Invoked code capability
# $c2		Invoked data capability
# $c3..$c10	Argument capabilities; $c3 as return capability
# $c11..$c16	n/a
# $c17..$c25	n/a
# $c26		IDC
#
# XXXRW: Worries/TODO:
#
# - Floating-point registers.
# - The compiler needs to handle unused argument/return registers.
#

	.text
	.global libcheri_invoke
	.global cheri_invoke
	.ent	libcheri_invoke
libcheri_invoke:
cheri_invoke:

	#
	# Wrap up all caller-save state suitable to be preseved by CCall and
	# restored by CReturn.  This happens in two phases:
	#
	# 1. First, use the conventional stack to save as many caller-save
	# general-purpose and capability registers as possible.
	#
	# 2. Produce a value for $csp that bundles these up suitable to
	# bootstrap restoration.  This will save the original $idc, $csp,
	# $sp, and $ddc.
	#
	# Then after CReturn, reverse these steps by first unwrapping $idc,
	# and then performing a more normal function return.
	#
	# The caller $csp will describe a stack fragment, which gives us a bit
	# of space to store useful things, such as $sp, that are otherwise
	# quite hard to restore (for obvious reasons).
	#
	# NB: This is still required for the hybrid ABI, unlike the
	# pure-capability ABI, because we need to save and restore $sp.
	#
	# Save callee-save general-purpose registers.
	#
	# Caller-save registers are: $s0..$s7, $gp, $sp, $s8 ($fp).
	#
	# Do also save $ra so that we can return properly.
	#
	# NB: Use 96 rather than 88 for the stack to ensure 32-byte alignment
	# for capabilities stored and loaded from it later.
	#
	# XXXRW: Possibly with the __ccall calling convention, the compiler
	# should be doing this?
	#
libcheri_invoke_save_regs:
	daddiu	$sp, -96
	sd	$s0, 0($sp)
	sd	$s1, 8($sp)
	sd	$s2, 16($sp)
	sd	$s3, 24($sp)
	sd	$s4, 32($sp)
	sd	$s5, 40($sp)
	sd	$s6, 48($sp)
	sd	$s7, 56($sp)
	sd	$gp, 64($sp)
	sd	$fp, 72($sp)
	sd	$ra, 80($sp)
	sd	$t9, 88($sp)

	#
	# Save capability registers we later need to restore (that won't be
	# handled by CCall for us).
	#
libcheri_invoke_save_caps:
	cgetdefault	$c11
	daddiu	$sp, -10*CHERICAP_SIZE
	csc	$c17, $sp, 0($c11)
	csc	$c18, $sp, 1*CHERICAP_SIZE($c11)
	csc	$c19, $sp, 2*CHERICAP_SIZE($c11)
	csc	$c20, $sp, 3*CHERICAP_SIZE($c11)
	csc	$c21, $sp, 4*CHERICAP_SIZE($c11)
	csc	$c22, $sp, 5*CHERICAP_SIZE($c11)
	csc	$c23, $sp, 6*CHERICAP_SIZE($c11)
	csc	$c24, $sp, 7*CHERICAP_SIZE($c11)
	csc	$c25, $sp, 8*CHERICAP_SIZE($c11)
	csc	$c26, $sp, 9*CHERICAP_SIZE($c11)

	#
	# Stash $sp in the offset of $c11 so that it will be saved and
	# restored by CCall.
	#
	csetoffset	$c11, $c11, $sp

	#
	# The compiler is responsible for scrubbing unused argument registers
	# (since only it has the information required to do so).  CCall is
	# responsible for scrubbing all other registers.
	#

	#
	# Construct link-address PCC.
	#
	# XXXRW: Do we want a CCall variant like CJALR that automatically
	# builds the desired capability?
	#
	dla		$t0, libcheri_invoke_ccall_linkaddr
	cgetpcc		$c17
	csetoffset	$c17, $c17, $t0

	#
	# Invoke object capability.  CCall/CReturn will save and restore $csp.
	#
libcheri_invoke_ccall:
	CCALL($c1, $c2)
libcheri_invoke_ccall_linkaddr:

	#
	# Unstash $sp from offset of $c11; restore $c11 offset to zero and
	# install as DDC.
	#
	cgetoffset	$sp, $c11
	csetoffset	$c11, $c11, $zero
	csetdefault	$c11

	#
	# Restore capability registers from stack.
	#
libcheri_invoke_restore_caps:
	clc	$c17, $sp, 0($c11)
	clc	$c18, $sp, 1*CHERICAP_SIZE($c11)
	clc	$c19, $sp, 2*CHERICAP_SIZE($c11)
	clc	$c20, $sp, 3*CHERICAP_SIZE($c11)
	clc	$c21, $sp, 4*CHERICAP_SIZE($c11)
	clc	$c22, $sp, 5*CHERICAP_SIZE($c11)
	clc	$c23, $sp, 6*CHERICAP_SIZE($c11)
	clc	$c24, $sp, 7*CHERICAP_SIZE($c11)
	clc	$c25, $sp, 8*CHERICAP_SIZE($c11)
	clc	$c26, $sp, 9*CHERICAP_SIZE($c11)

libcheri_invoke_set_errno:
	bnez	$a0, libcheri_set_errno
	daddiu	$sp, 10*CHERICAP_SIZE		# Branch-delay slot

	#
	# CCall has conservatively cleared all non-return-value registers, and
	# so we don't need to.

	#
	# Restore general-purpose registers from the stack.
	#
libcheri_invoke_restore_regs:
	ld	$s0, 0($sp)
	ld	$s1, 8($sp)
	ld	$s2, 16($sp)
	ld	$s3, 24($sp)
	ld	$s4, 32($sp)
	ld	$s5, 40($sp)
	ld	$s6, 48($sp)
	ld	$s7, 56($sp)
	ld	$gp, 64($sp)
	ld	$fp, 72($sp)
	ld	$ra, 80($sp)
	daddiu	$sp, 96

	#
	# Return to C-language caller.
	#
libcheri_invoke_return:
	jr	$ra
	nop				# Branch-delay slot

libcheri_set_errno:
#ifndef __PIC__
	lui     $at, %tprel_hi(libcheri_errno)
	.set    push
	.set    mips32r2
	rdhwr   $t0, $29
	.set    pop
	daddiu  $at, $at, %tprel_lo(libcheri_errno)
	daddu   $at, $t0, $at
	sw      $a0, 0($at)
#else
	ld	$t9, 88($sp)
	sd	$a0, 88($sp)
	#
	# Set up $gp.
	#
	lui	$at, %hi(%neg(%gp_rel(libcheri_invoke)))
	daddu	$at, $at, $t9
	daddiu	$gp, $at, %lo(%neg(%gp_rel(libcheri_invoke)))
	#
	# Get the address of the thread-local libcheri_errno variable.
	#
	lui	$at, %call_hi(__tls_get_addr)
	daddu	$at, $at, $gp
	ld	$t9, %call_lo(__tls_get_addr)($at)
	jalr	$t9
	daddiu	$a0, $gp, %tlsgd(libcheri_errno)
	#
	# Store the signal value in libcheri_errno.
	#
	ld	$a0, 88($sp)
	sw	$a0, 0($v0)
#endif // __PIC__
	#
	# Store the values in v0 / v1 that code that doesn't know about
	# libcheri_errno might be expecting.
	#
	daddiu	$v0, $zero, -1
	b	libcheri_invoke_restore_regs
	move	$v1, $a0

	.end	libcheri_invoke

	.type	libcheri_errno,@object      # @libcheri_errno
	.section	.tbss,"awT",@nobits
	.globl	libcheri_errno
	.align	2
libcheri_errno:
	.4byte	0                       # 0x0
	.size	libcheri_errno, 4
