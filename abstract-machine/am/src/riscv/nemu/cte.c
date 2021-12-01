#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {
  printf("Running ## __am_irq_handle() ##\n...\n");
  // for (int i = 0; i < 33; ++i) {
  //   printf("(%d) 0x%08x\t", i, *(c + i));
  //   if (i % 8 == 7) printf("\n");
  // }
  printf("(1) 0x%08x\n(2) 0x%08x\n", c->ra, c->gp);
  printf("%d\n", &c->mstatus-&c->mcause);
  if (user_handler) {
    Event ev = {0};
    switch (c->mcause) {
      case 1: ev.event = EVENT_YIELD; break;
      default: ev.event = EVENT_ERROR; break;
    }

    c = user_handler(ev, c);
    assert(c != NULL);
  }

  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  return NULL;
}

void yield() {
  asm volatile("li a7, -1; ecall");
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
