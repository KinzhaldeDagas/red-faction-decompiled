// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046F950 rf_demo_upsell_initialize
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): Loads demo-upsell1.tga/2.tga/3.tga into handles6F9100/04/08 with(-1,0), sets index6F910C=0, arms minimum-advance deadline6F9114 for1000ms and display deadline6F9110 from
// original duration table66244C[index]. Durations for slides0..2 are4000/10000/5000ms. No own build latch, previous-handle free or load-failure gate.
int rf_demo_upsell_initialize()
{
  unk_6F9100[0] = rf_bitmap_load_with_optional_mipmap_generation("demo-upsell1.tga", (void *)0xFFFFFFFF, 0);
  unk_6F9104 = rf_bitmap_load_with_optional_mipmap_generation("demo-upsell2.tga", (void *)0xFFFFFFFF, 0);
  unk_6F9108 = rf_bitmap_load_with_optional_mipmap_generation("demo-upsell3.tga", (void *)0xFFFFFFFF, 0);
  unk_6F910C = 0;
  rf_clock_deadline_set_wrapped_offset(&dword_6F9114, 1000);
  return rf_clock_deadline_set_wrapped_offset(&dword_6F9110, dword_66244C[unk_6F910C]);
}

