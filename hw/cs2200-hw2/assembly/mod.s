!============================================================
! CS 2200 Homework 2 Part 1: mod
!
! Edit any part of this file necessary to implement the
! mod operation. Store your result in $v0.
!============================================================

mod:
    addi    $a0, $zero, 28      ! $a0 = 28, the number a to compute mod(a,b), also x
    addi    $a1, $zero, 13      ! $a1 = 13, the number b to compute mod(a,b)
    nand    $t0, $a1, $a1       ! $t0 = ~$a1, ~b
    addi    $t0, $t0, 1         ! $t0 = -$a1, -b
loop:
    blt     $a0, $a1, done      ! if x < b go to done
    add     $a0, $a0, $t0       ! x = x - b
    beq     $zero, $zero, loop
done:
    add     $v0, $zero, $a0     ! return x
    halt
