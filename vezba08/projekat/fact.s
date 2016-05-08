################################################################################
#  Odsek za racunarsku tehniku i medjuracunarske komunikacije                  #
################################################################################
#                                                                              #
# Naziv Modula: fact.s                                                         #
#                                                                              #
# Opis: izracunavanje faktorijela vrednosti smestene na lokaciji value         #
#                                                                              #
################################################################################

.globl main

.data

value: .word 9

.text

.space 7

main:
              la    $t1, value     # ucitavanje adrese
              lw    $t2, 0($t1)    # ucitavanje vrednosti faktorijela sa adrese u $t1

              add   $t3, $t2, $0   # postavljanje rezultata na value

              addi  $t1, $0, 1
              sub   $t2, $t2, $t1  # umanjivanje brojaca

              blez  $t2, exit
              nop

loop:
              mult  $t3, $t2
              MFLO  $t3

              sub   $t2, $t2, $t1  # umanjivanje brojaca

              blez  $t2, exit
              nop

              b     loop

exit:         nop
