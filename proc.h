#pragma once


#ifndef _PROC_H
#define _PROC_H
//error remember to put multi-include protection in here



#ifdef PROC_TIMES
 //error you will need a couple additional include files
#include "date.h"
#endif // PROC_TIMES


#ifdef LOTTERY
// error some new defines go in here. things like default, min, and max nice values
#ifndef DEFAULT_NICE_VALUE
#define DEFAULT_NICE_VALUE 40
#endif // DNV
#ifndef MAX_NICE_VALUE
#define MAX_NICE_VALUE 100
#endif // MAX_NV
#ifndef MIN_NICE_VALUE
#define MIN_NICE_VALUE 1
#endif // MIN_NV
#endif // LOTTERY


// Per-CPU state
struct cpu {
  uchar apicid;                // Local APIC ID
  struct context *scheduler;   // swtch() here to enter scheduler
  struct taskstate ts;         // Used by x86 to find stack for interrupt
  struct segdesc gdt[NSEGS];   // x86 global descriptor table
  volatile uint started;       // Has the CPU started?
  int ncli;                    // Depth of pushcli nesting.
  int intena;                  // Were interrupts enabled before pushcli?
  struct proc *proc;           // The process running on this cpu or null
};

extern struct cpu cpus[NCPU];
extern int ncpu;

//PAGEBREAK: 17
// Saved registers for kernel context switches.
// Don't need to save all the segment registers (%cs, etc),
// because they are constant across kernel contexts.
// Don't need to save %eax, %ecx, %edx, because the
// x86 convention is that the caller has saved them.
// Contexts are stored at the bottom of the stack they
// describe; the stack pointer is the address of the context.
// The layout of the context matches the layout of the stack in swtch.S
// at the "Switch stacks" comment. Switch doesn't save eip explicitly,
// but it is on the stack and allocproc() manipulates it.
struct context {
  uint edi;
  uint esi;
  uint ebx;
  uint ebp;
  uint eip;
};

enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

// Per-process state
struct proc {
  uint sz;                     // Size of process memory (bytes)
  pde_t* pgdir;                // Page table
  char *kstack;                // Bottom of kernel stack for this process
  enum procstate state;        // Process state
  int pid;                     // Process ID
  struct proc *parent;         // Parent process
  struct trapframe *tf;        // Trap frame for current syscall
  struct context *context;     // swtch() here to run process
  void *chan;                  // If non-zero, sleeping on chan
  int killed;                  // If non-zero, have been killed
  struct file *ofile[NOFILE];  // Open files
  struct inode *cwd;           // Current directory
  char name[16];               // Process name (debugging)

#ifdef PROC_TIMES
// error some new structure members go in here
    struct rtcdate begin_date;
    uint ticks_total;   //Represents the total num of time ticks that the process has run
    uint ticks_begin;   // Helps to calculate the total num of time ticks the process has used
    uint sched_times;   // Used to count the number of times the process has been scheduled to run
#endif // PROC_TIMES

# ifdef LOTTERY
//error something nice should go in here
    uint nice_value;
# endif // LOTTERY
};

// Process memory is laid out contiguously, low addresses first:
//   text
//   original data and bss
//   fixed-size stack
//   expandable heap



#endif // _PROC_H







