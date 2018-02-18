//
// idt_handlers.c
//
// Created by Piotr Merski on 18.02.18
//

#include "idt.h"
#include "idt_handlers.h"

#define interrput_exit __asm("iret")

void isr_division_by_zero() {
    interrput_exit;
}

void isr_debug_exception() {
    interrput_exit;
}

void isr_non_maskable_interrput() {
    interrput_exit;
}

void isr_breakpoint_exception() {
    interrput_exit;
}

void isr_detected_overflow() {
    interrput_exit;
}

void isr_out_of_bounds_exception() {
    interrput_exit;
}

void isr_invalid_opcode_exception() {
    interrput_exit;
}

void isr_no_coprocessor_exception() {
    interrput_exit;
}

void isr_double_fault(u8int error_code) {
    interrput_exit;
}

void isr_coprocessor_segment_overrun() {
    interrput_exit;
}

void isr_bad_tss(u8int error_code) {
    interrput_exit;
}

void isr_segment_not_present(u8int error_code) {
    interrput_exit;
}

void isr_stack_fault(u8int error_code) {
    interrput_exit;
}

void isr_general_protection_fault(u8int error_code) {
    interrput_exit;
}

void isr_page_fault(u8int error_code) {
    interrput_exit;
}

void isr_reserved_15() {
    interrput_exit;
}

void isr_coprocessor_fault() {
    interrput_exit;
}

void isr_alignment_check_exception(u8int error_code) {
    interrput_exit;
}

void isr_machine_check_exception() {
    interrput_exit;
}

void isr_reserved_from_19_to_31() {
    interrput_exit;
}