// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00412A80 sub_412A80
// UNREALRED VERIFIED [combat-panic-20261104]: Embedded AI constructor called by412740 atEntity+2A0 constructs timestamps+250,+254,+258 through55EF40 (writes-1). In particular fresh panic+254 is unarmed.4033C0 later arms fear+250 and voice+4E4 but does not initialize/arm panic+254. With55F0B0 returning fullPeriod for negative deadlines, ordinary5..10s40B1A0 cannot arm that fresh panic deadline. Preserve this actual initialization/comparison; do not invent a timed restore.
char *__thiscall sub_412A80(char *this)
{
  rf_dword_array_construct_capacity(this + 524, 0);
  rf_timestamp4_construct_invalid((int *)this + 134);
  rf_timestamp4_construct_invalid((int *)this + 135);
  rf_vector_construct_no_unwind(this + 544, 4u, 2, (void *(__thiscall *)(void *))rf_timestamp4_construct_invalid);
  rf_timestamp4_construct_invalid((int *)this + 139);
  rf_timestamp4_construct_invalid((int *)this + 140);
  rf_timestamp4_construct_invalid((int *)this + 141);
  rf_timestamp4_construct_invalid((int *)this + 142);
  rf_timestamp4_construct_invalid((int *)this + 143);
  rf_vector3_default_construct_noop(this + 576);
  rf_timestamp4_construct_invalid((int *)this + 148);
  rf_timestamp4_construct_invalid((int *)this + 149);
  rf_timestamp4_construct_invalid((int *)this + 150);
  rf_timestamp4_construct_invalid((int *)this + 151);
  rf_timestamp4_construct_invalid((int *)this + 153);
  rf_timestamp4_construct_invalid((int *)this + 157);
  rf_timestamp4_construct_invalid((int *)this + 158);
  rf_timestamp4_construct_invalid((int *)this + 165);
  rf_timestamp4_construct_invalid((int *)this + 168);
  rf_timestamp4_construct_invalid((int *)this + 169);
  rf_timestamp4_construct_invalid((int *)this + 170);
  rf_vector3_default_construct_noop(this + 708);
  rf_timestamp4_construct_invalid((int *)this + 180);
  rf_timestamp4_construct_invalid((int *)this + 183);
  rf_timestamp4_construct_invalid((int *)this + 184);
  rf_dual_pose_aggregate_construct_invalid_timestamps(this + 744);
  rf_force_sample44_construct_vectors_noop(this + 1128);
  rf_timestamp4_construct_invalid((int *)this + 291);
  rf_vector3_default_construct_noop(this + 1168);
  rf_timestamp4_construct_invalid((int *)this + 297);
  rf_timestamp4_construct_invalid((int *)this + 301);
  rf_timestamp4_construct_invalid((int *)this + 302);
  rf_timestamp4_construct_invalid((int *)this + 305);
  rf_timestamp4_construct_invalid((int *)this + 308);
  rf_timestamp4_construct_invalid((int *)this + 309);
  rf_timestamp4_construct_invalid((int *)this + 310);
  rf_timestamp4_construct_invalid((int *)this + 311);
  rf_timestamp4_construct_invalid((int *)this + 312);
  rf_timestamp4_construct_invalid((int *)this + 313);
  rf_timestamp4_construct_invalid((int *)this + 314);
  rf_vector3_default_construct_noop(this + 1260);
  rf_timestamp4_construct_invalid((int *)this + 318);
  rf_timestamp4_construct_invalid((int *)this + 319);
  rf_vector3_default_construct_noop(this + 1280);
  return this;
}

