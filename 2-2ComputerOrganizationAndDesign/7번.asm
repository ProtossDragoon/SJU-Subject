.globl main
.data
one: .asciiz "a is : "
two: .asciiz "n is : "
blank: .asciiz "  "

.text
main:
la $a0 one
li $v0 4
syscall #"A : " 문자열 출력
li $v0 5
syscall #숫자 입력
add $t0 $v0 $zero #입력된 숫자 레지스터에 복사


la $a0 two
li $v0 4
syscall #"N : " 문자열 출력
li $v0 5
syscall #숫자 입력
add $t1 $v0 $zero #입력된 숫자 레지스터에 복사


#------ set variables ------#
addi $a0 $t0 0 # a0 = A
addi $a1 $t1 0 # a1 = N
addi $t0 $a1 -1 # t0 = N-1
addi $t1 $a1 -2 # t1 = N-2
addi $s0 $zero 2 #s0 = 2
#------------------------------#


jal Tfunction
j exit

Tfunction :
addi $sp $sp -24
sw $ra 20($sp)
sw $s1 16($sp)
sw $v0 12($sp)
sw $a1 8($sp)
sw $t0 4($sp)
sw $t1 0($sp)

blt $a1 $s0 lessthan2 #if  n < 2
j biggerthan1 #else n >= 2

#-----------------
lessthan2 :
addi $v0 $zero 1
jr $ra
#-----------------
biggerthan1 :

lw $a1 4($sp)
addi $t0 $a1 -1
addi $t1 $a1 -2
jal Tfunction
add $t8 $v0 $zero

lw $a1 0($sp)
addi $t0 $a1 -1
addi $t1 $a1 -2
jal Tfunction
add $t9 $v0 $zero

j summation
#-----------------

summation :
add $t7 $t8 $t9
add $v0 $t7 $s1
add $v0 $t7 $a0
add $s1 $s1 $v0


addi $sp $sp 48
lw $ra 20($sp)
jr $ra


exit :

addi $v0 $s1 0
addi $t5 $a0 0

addi $a0 $v0 0
li $v0 1
syscall
la $a0 blank
li $v0 4
syscall

