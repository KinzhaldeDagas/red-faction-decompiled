// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CCC30 rf_particle_draw_usage_debug_hud
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Cdecl debug HUD, gated by nonzero BYTE 0x8377DC. Formats sum of signed active counts 0x8666F8 + 0x8667F4 and draws "particles used: " at screen (10,10), font 0x182ABBC, length -1.
// Updates signed peak 0x8377E0 when total is greater. Only while signed sample counter 0x662DF0<10000, adds total to DOUBLE 0x8377E8 and increments the counter. Average display is
// floor_float(F32(double_sum / signed_counter + double 0.5)), converted through __ftol2_sse. Pool initialization sets sum=0,counter=1: first enabled sample divides by 2. Samples are
// collected only during enabled HUD calls and freeze at counter 10000; current count and peak still update afterward.
// Draws "max: ...  avg: ..." at (10,20) and "moved: ...  rendered: ..." using 0x8377E4/0x8377F0 at (10,30). RFString temporaries and unwind cleanup destroy their buffers. This
// formats counters; it neither updates particle motion nor renders particle billboards.
void rf_particle_draw_usage_debug_hud()
{
  unsigned __int8 *v0; // eax
  double v1; // st7
  unsigned __int8 *v2; // eax
  unsigned __int8 *v3; // eax
  int value; // [esp+0h] [ebp-DCh]
  int valuea; // [esp+0h] [ebp-DCh]
  int valueb; // [esp+0h] [ebp-DCh]
  void *v7; // [esp+8h] [ebp-D4h]
  int *v8; // [esp+10h] [ebp-CCh]
  _DWORD *v9; // [esp+18h] [ebp-C4h]
  const void **v10; // [esp+20h] [ebp-BCh]
  _DWORD *v11; // [esp+28h] [ebp-B4h]
  void *v12; // [esp+30h] [ebp-ACh]
  int *v13; // [esp+38h] [ebp-A4h]
  _DWORD *v14; // [esp+40h] [ebp-9Ch]
  const void **v15; // [esp+48h] [ebp-94h]
  _DWORD *v16; // [esp+50h] [ebp-8Ch]
  float v17; // [esp+58h] [ebp-84h]
  const void **v18; // [esp+60h] [ebp-7Ch]
  _BYTE v19[8]; // [esp+68h] [ebp-74h] BYREF
  _BYTE v20[8]; // [esp+70h] [ebp-6Ch] BYREF
  _BYTE v21[8]; // [esp+78h] [ebp-64h] BYREF
  _DWORD v22[2]; // [esp+80h] [ebp-5Ch] BYREF
  _DWORD v23[2]; // [esp+88h] [ebp-54h] BYREF
  _BYTE v24[8]; // [esp+90h] [ebp-4Ch] BYREF
  _BYTE v25[8]; // [esp+98h] [ebp-44h] BYREF
  _BYTE v26[8]; // [esp+A0h] [ebp-3Ch] BYREF
  _DWORD v27[2]; // [esp+A8h] [ebp-34h] BYREF
  _DWORD v28[2]; // [esp+B0h] [ebp-2Ch] BYREF
  _DWORD v29[2]; // [esp+B8h] [ebp-24h] BYREF
  _DWORD v30[2]; // [esp+C0h] [ebp-1Ch] BYREF
  double v31; // [esp+C8h] [ebp-14h]
  int v32; // [esp+D8h] [ebp-4h]

  if ( unk_8377DC )
  {
    v18 = (const void **)rf_string_format_int32_decimal(v29, unk_8667F4 + unk_8666F8);
    v32 = 0;
    rf_string_concat_cstr_object(v30, "particles used: ", v18);
    LOBYTE(v32) = 2;
    rf_string_destroy_buffer(v29);
    value = dword_182ABBC;
    v0 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v30);
    rf_font_draw_text_screen(10, 10, v0, -1, value);
    if ( unk_8667F4 + unk_8666F8 > dword_8377E0 )
      dword_8377E0 = unk_8667F4 + unk_8666F8;
    if ( dword_662DF0 < 10000 )
    {
      unk_8377E8 = (double)(unk_8667F4 + unk_8666F8) + unk_8377E8;
      ++dword_662DF0;
    }
    v31 = unk_8377E8 / (double)dword_662DF0;
    v17 = v31 + 0.5;
    v1 = rf_floor_float(v17);
    v16 = rf_string_format_int32_decimal(v28, (int)v1);
    LOBYTE(v32) = 3;
    v15 = (const void **)rf_string_format_int32_decimal(v27, dword_8377E0);
    LOBYTE(v32) = 4;
    v14 = rf_string_concat_cstr_object(v26, "max: ", v15);
    LOBYTE(v32) = 5;
    v13 = (int *)rf_string_concat_object_cstr(v25, v14, "  avg: ");
    LOBYTE(v32) = 6;
    v12 = rf_string_concat_two_objects(v24, v13, (int)v16);
    LOBYTE(v32) = 7;
    rf_string_assign_from_object(v30, (int)v12);
    LOBYTE(v32) = 6;
    rf_string_destroy_buffer(v24);
    LOBYTE(v32) = 5;
    rf_string_destroy_buffer(v25);
    LOBYTE(v32) = 4;
    rf_string_destroy_buffer(v26);
    LOBYTE(v32) = 3;
    rf_string_destroy_buffer(v27);
    LOBYTE(v32) = 2;
    rf_string_destroy_buffer(v28);
    valuea = dword_182ABBC;
    v2 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v30);
    rf_font_draw_text_screen(10, 20, v2, -1, valuea);
    v11 = rf_string_format_int32_decimal(v23, unk_8377F0);
    LOBYTE(v32) = 8;
    v10 = (const void **)rf_string_format_int32_decimal(v22, unk_8377E4);
    LOBYTE(v32) = 9;
    v9 = rf_string_concat_cstr_object(v21, "moved: ", v10);
    LOBYTE(v32) = 10;
    v8 = (int *)rf_string_concat_object_cstr(v20, v9, "  rendered: ");
    LOBYTE(v32) = 11;
    v7 = rf_string_concat_two_objects(v19, v8, (int)v11);
    LOBYTE(v32) = 12;
    rf_string_assign_from_object(v30, (int)v7);
    LOBYTE(v32) = 11;
    rf_string_destroy_buffer(v19);
    LOBYTE(v32) = 10;
    rf_string_destroy_buffer(v20);
    LOBYTE(v32) = 9;
    rf_string_destroy_buffer(v21);
    LOBYTE(v32) = 8;
    rf_string_destroy_buffer(v22);
    LOBYTE(v32) = 2;
    rf_string_destroy_buffer(v23);
    valueb = dword_182ABBC;
    v3 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v30);
    rf_font_draw_text_screen(10, 30, v3, -1, valueb);
    v32 = -1;
    rf_string_destroy_buffer(v30);
  }
}

