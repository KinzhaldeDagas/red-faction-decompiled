// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00471CD0 rf_ui_cycle_list_append_text
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): Native ECX=this, STACK(text,font), RET8; incoming EDX is NOT used despite stored fastcall extra register parameter, which is retained. Signed
// countDWORD360<16 only; no lower bound. Measures text into width232+4*count,height296+4*count. Width<=0 returns without count increment (but measured slot changed). Else creates
// format4 bitmap(itemWH) into handles40+4*count, draws text at(0,0), then adds texture reference, WITHOUT clear or handle-failure guard. Computes signed centered
// offsets104/168=(controlWH-itemWH)/2, increments count. No duplicate filtering, old slot release, selection correction or count normalization. Return EAX is incidental and path
// dependent, not append-success boolean.
_DWORD *__fastcall rf_ui_cycle_list_append_text(_DWORD *a1, int a2, char *a3, int a4)
{
  _DWORD *result; // eax

  result = a1;
  if ( (int)a1[90] < 16 )
  {
    rf_font_measure_text_extent(&a1[a1[90] + 58], &a1[a1[90] + 74], (unsigned __int8 *)a3, strlen(a3), a4);
    result = (_DWORD *)a1[90];
    if ( (int)a1[(_DWORD)result + 58] > 0 )
    {
      a1[a1[90] + 10] = rf_bitmap_create_user_bitmap(4, a1[a1[90] + 58], a1[a1[90] + 74]);
      rf_font_draw_text_into_bitmap(0, 0, a1[a1[90] + 10], a3, a4);
      rf_bitmap_texture_add_reference_backend_dispatch(a1[a1[90] + 10]);
      a1[a1[90] + 26] = (a1[5] - a1[a1[90] + 58]) / 2;
      a1[a1[90] + 42] = (a1[6] - a1[a1[90] + 74]) / 2;
      ++a1[90];
      return a1;
    }
  }
  return result;
}

