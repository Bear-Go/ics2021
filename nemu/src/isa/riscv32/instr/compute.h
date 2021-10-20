def_EHelper(lui) {
  rtl_li(s, ddest, id_src1->imm);
}

//My own code below

def_EHelper(li) {
  // wait
  rtl_li(s, ddest, id_src1->imm);
}

def_EHelper(auipc) {
  // wait
  rtl_li(s, ddest, s->pc + id_src1->imm);
}

def_EHelper(addi) {
  // wait
  rtl_addi(s, ddest, dsrc1, id_src2->imm);
}

def_EHelper(jal) {
  // wait
  rtl_li(s, ddest, s->snpc);
  rtl_j(s, s->pc + id_src1->imm);
}

def_EHelper(ret) {
  // wait
  rtl_jr(s, dsrc1);
}

def_EHelper(beq) {
  rtl_jrelop(s, RELOP_EQ, dsrc1, dsrc2, id_dest->imm);
}

def_EHelper(add) {
  rtl_add(s, ddest, dsrc1, dsrc2);
}

// def_EHelper(j) {
//   //wait
//   rtl_j(s, id_src1->imm);
// }