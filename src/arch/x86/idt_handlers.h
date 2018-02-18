//
// idt_handlers.h
//
// Created by Piotr Merski on 18.02.18
//

#pragma once

void isr_division_by_zero();
void isr_debug_exception();
void isr_non_maskable_interrput();
void isr_breakpoint_exception();
void isr_detected_overflow();
void isr_out_of_bounds_exception();
void isr_invalid_opcode_exception();
void isr_no_coprocessor_exception();
void isr_double_fault(u8int error_code);
void isr_coprocessor_segment_overrun();
void isr_bad_tss(u8int error_code);
void isr_segment_not_present(u8int error_code);
void isr_stack_fault(u8int error_code);
void isr_general_protection_fault(u8int error_code);
void isr_page_fault(u8int error_code);
void isr_reserved_15();
void isr_coprocessor_fault();
void isr_alignment_check_exception(u8int error_code);
void isr_machine_check_exception();
void isr_reserved_from_19_to_31();
