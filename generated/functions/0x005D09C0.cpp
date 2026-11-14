// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D09C0 rf_renderer_apply_packed_render_state
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, all packed-state selector branches, original-PE device-call immediates and option/cache paths): Full branch mapping reverified,including texture modes0..11,RGB/alpha payload flags,blend/depth/fog and unsupported selectors. Descriptor has six5-bit fields at shifts0,5,10,15,20,25;bits30/31 ignored by getters but compared by whole-word cache. Texture4 rewritten in LOCAL BY-VALUE copy to5 ONLY when byte1DAEDF5 EXACT1 before fullDWORD cache comparison. Equal cache1E014FC returns immediately (including no sampler/fog refresh). Changed descriptor calls begin_immediate_buffers(4,3) when byte1E014E5 set,stores cache BEFORE device calls and never rolls back on failed HRESULT. Always writes stage0 LOD bias from664A48(initial PE float-0.75;only direct xref is this read). Device vtable252=texture-stage state,200=render state;all
// results ignored except incidental AL return. Texture defaults/mode7 and out-of-range selector domains inherit previous device state;no complete device-state reset or validity check. Case-address comments supply exact numeric TSS maps;abbreviations TSS(stage,state,value),CO=1,CA1=2,CA2=3,AO=4,AA1=5,AA2=6,UV11,U13/V14,MAG16/MIN17/MIP18/BIAS19. Operations1=DISABLE,2=SELECTARG1,3=SELECTARG2,4=MODULATE,5=MODULATE2X,7=ADD,8=ADDSIGNED;arguments0=DIFFUSE,1=CURRENT,2=TEXTURE. Diffuse-RGB payload byte664A3C:RGB selectors0,2,3,4=>1,selector1=>0,others unchanged. Diffuse-alpha byte664A3D:selectors0,1,3=>1,2=>0,others unchanged. Blend map RS27enable/19src/20dst:0 disable;1(ONE,ONE);2/4(SRCALPHA,ONE);3(SRCALPHA,INVSRCALPHA) if capability word1DAE83C bit0x10,else SRC=BOTHSRCALPHA12 with no explicit destination write;5(DESTCOLOR,ZERO) ONLY when capability bit0x100 else NO blend
// writes;6(INVDESTCOLOR,ZERO);7(DESTCOLOR,SRCCOLOR);unsupported inherits. Depth map RS15alphaTest,7ZEnable,14ZWrite,23ZFunc:selector0 off/off/off;1 alphaoff,Z convention,no writes,conventionFunc;2 same but EQUAL3;3 alphaoff/Zoff/writeon;4 alphaoff,Z convention/writeon,conventionFunc;5 same Z/write/FUNC then alphaTestON,ALPHAREF16,ALPHAFUNC GREATER7. Convention global187CD1C:0 ZEnable1/FuncGEQUAL7;1 ZEnableUSEW2/FuncLEQUAL4;other ZEnable0/FuncLEQUAL4. CORRECTION: old annotation swapped RS24/25 and claimed reference7;actual RS24=16,RS25=7,so first admitted 8-bit alpha is17. Fog selectors0..2 all enable RS28 only when RF flag187CCF0 nonzero,applied-fog byte1E014E4 then equals(global664A14==2);otherwise clear byte/disable. Fog3 always clear/disable;others unchanged. No mode writes stage1 LOD bias;only modes10/11 force stage1 MIPLINEAR without consulting detail toggle. Return is cache-equality
// bool on early path or truncated incidental last-call/register value on changed path,not reliable apply-success.
char __cdecl rf_renderer_apply_packed_render_state(int a1)
{
  char result; // al
  int depth_alpha_test_selector; // [esp+28h] [ebp-18h]
  int alpha_modulation_selector; // [esp+2Ch] [ebp-14h]
  int texture_mode; // [esp+30h] [ebp-10h]
  int rgb_modulation_selector; // [esp+34h] [ebp-Ch]
  int blend_selector; // [esp+38h] [ebp-8h]
  int fog_selector; // [esp+3Ch] [ebp-4h]

  if ( rf_render_state_get_texture_mode(&a1) == 4 && unk_1DAEDF5 == 1 )
    rf_render_state_set_texture_mode(&a1, 5);
  result = rf_packed_state_word_equal(&a1, &dword_1E014FC);
  if ( !result )
  {
    if ( unk_1E014E5 )
      rf_renderer_begin_immediate_buffers(4, 3);
    dword_1E014FC = a1;
    texture_mode = rf_render_state_get_texture_mode(&a1);
    rgb_modulation_selector = rf_render_state_get_rgb_modulation_selector(&a1);
    alpha_modulation_selector = rf_render_state_get_alpha_modulation_selector(&a1);
    blend_selector = rf_render_state_get_blend_selector(&a1);
    depth_alpha_test_selector = rf_render_state_get_depth_alpha_test_selector(&a1);
    fog_selector = rf_render_state_get_fog_selector(&a1);
    (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
      dword_1DAEDC4,
      dword_1DAEDC4,
      0,
      19,
      rf_stage0_texture_lod_bias);
    switch ( texture_mode )
    {
      case 0:
        rf_renderer_bind_texture_handle(0, -1, 0, 0, 0, 0);
        rf_renderer_bind_texture_handle(1, -1, 0, 0, 0, 0);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          1,
          2);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 2, 0);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 4, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          5,
          0);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 1, 1);
        break;
      case 1:
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 13, 1);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          14,
          1);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 17, 2);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 16, 2);
        switch ( rgb_modulation_selector )
        {
          case 3:
            (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
              dword_1DAEDC4,
              dword_1DAEDC4,
              0,
              1,
              7);
            break;
          case 4:
            (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 1, 5);
            break;
          case 2:
            (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 1, 4);
            break;
          default:
            (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
              dword_1DAEDC4,
              dword_1DAEDC4,
              0,
              1,
              2);
            break;
        }
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 2, 2);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 3, 0);
        switch ( alpha_modulation_selector )
        {
          case 3:
            (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
              dword_1DAEDC4,
              dword_1DAEDC4,
              0,
              4,
              4);
            goto LABEL_32;
          case 2:
            goto LABEL_31;
          case 0:
            (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 4, 3);
            break;
        }
        goto LABEL_32;
      case 2:
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          13,
          3);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 14, 3);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 17, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          16,
          2);
        switch ( rgb_modulation_selector )
        {
          case 3:
            (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 1, 7);
            break;
          case 4:
            (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 1, 5);
            break;
          case 2:
            (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
              dword_1DAEDC4,
              dword_1DAEDC4,
              0,
              1,
              4);
            break;
          default:
            (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 1, 2);
            break;
        }
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 2, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          3,
          0);
        if ( alpha_modulation_selector == 3 )
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 4, 4);
        else
LABEL_31:
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 4, 2);
LABEL_32:
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          5,
          2);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 6, 0);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 1, 1);
        break;
      case 3:
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          13,
          3);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 14, 3);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 17, 1);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          16,
          1);
        if ( rgb_modulation_selector == 3 )
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 1, 7);
        else
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 1, 4);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          2,
          2);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 3, 0);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 4, 4);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          5,
          2);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 6, 0);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 1, 1);
        break;
      case 4:
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          17,
          2);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 16, 2);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 1, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          2,
          2);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 3, 0);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 4, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          5,
          2);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 6, 0);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 13, 1);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          14,
          1);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 11, 0);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 17, 2);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          16,
          2);
        if ( rgb_modulation_selector == 3 )
          (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 1, 7);
        else
          (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 1, 4);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          2,
          2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 3, 1);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 4, 1);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          5,
          2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 6, 1);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 13, 3);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          14,
          3);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 11, 1);
        break;
      case 5:
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 17, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          16,
          2);
        if ( rgb_modulation_selector == 2 )
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 1, 4);
        else
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 1, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          2,
          2);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 3, 0);
        if ( alpha_modulation_selector == 3 )
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 4, 4);
        else
          (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
            dword_1DAEDC4,
            dword_1DAEDC4,
            0,
            4,
            2);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 5, 2);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 6, 0);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          13,
          1);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 14, 1);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 11, 0);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          17,
          2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 16, 2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 1, 5);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          2,
          2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 3, 1);
        if ( rf_d3d8_voodoo3_compatibility_mode )
          (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
            dword_1DAEDC4,
            dword_1DAEDC4,
            1,
            4,
            2);
        else
          (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 4, 3);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 5, 2);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          6,
          1);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 13, 3);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 14, 3);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          11,
          1);
        break;
      case 6:
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 17, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          16,
          2);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 1, 2);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 2, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          3,
          0);
        if ( alpha_modulation_selector == 3 )
        {
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 4, 4);
        }
        else if ( alpha_modulation_selector )
        {
          if ( alpha_modulation_selector == 2 )
            (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
              dword_1DAEDC4,
              dword_1DAEDC4,
              0,
              4,
              2);
        }
        else
        {
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 4, 3);
        }
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 5, 2);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 6, 0);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          13,
          3);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 14, 3);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 11, 0);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          17,
          2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 16, 2);
        if ( rgb_modulation_selector == 3 )
          (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 1, 7);
        else
          (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
            dword_1DAEDC4,
            dword_1DAEDC4,
            1,
            1,
            5);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 2, 2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 3, 1);
        if ( rf_d3d8_voodoo3_compatibility_mode )
          goto LABEL_51;
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 4, 3);
        goto LABEL_53;
      case 8:
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 17, 2);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 16, 2);
        if ( rgb_modulation_selector == 2 )
          (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
            dword_1DAEDC4,
            dword_1DAEDC4,
            0,
            1,
            4);
        else
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 1, 2);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 2, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          3,
          0);
        if ( alpha_modulation_selector == 3 )
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 4, 4);
        else
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 4, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          5,
          2);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 6, 0);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 13, 1);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          14,
          3);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 11, 0);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 17, 2);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          16,
          2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 1, 5);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 2, 2);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          3,
          1);
        if ( rf_d3d8_voodoo3_compatibility_mode )
          (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 4, 2);
        else
          (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
            dword_1DAEDC4,
            dword_1DAEDC4,
            1,
            4,
            1);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 5, 2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 6, 1);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          13,
          3);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 14, 3);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 11, 1);
        break;
      case 9:
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          17,
          2);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 16, 2);
        if ( rgb_modulation_selector == 2 )
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 1, 4);
        else
          (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
            dword_1DAEDC4,
            dword_1DAEDC4,
            0,
            1,
            2);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 2, 2);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 3, 0);
        if ( alpha_modulation_selector == 3 )
          (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
            dword_1DAEDC4,
            dword_1DAEDC4,
            0,
            4,
            4);
        else
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 4, 2);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 5, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          6,
          0);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 13, 3);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 14, 1);
        (*(void (__thiscall **)(int, int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          11,
          0);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 17, 2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 16, 2);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          1,
          5);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 2, 2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 3, 1);
        if ( rf_d3d8_voodoo3_compatibility_mode )
LABEL_51:
          (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 4, 2);
        else
          (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 4, 1);
LABEL_53:
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          5,
          2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 6, 1);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 13, 3);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          14,
          3);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 11, 1);
        break;
      case 10:
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 17, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          16,
          2);
        if ( rgb_modulation_selector == 2 )
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 1, 4);
        else
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 1, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          2,
          2);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 3, 0);
        if ( alpha_modulation_selector == 3 )
          (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 4, 4);
        else
          (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
            dword_1DAEDC4,
            dword_1DAEDC4,
            0,
            4,
            2);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 5, 2);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 6, 0);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          13,
          1);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 14, 1);
        (*(void (__stdcall **)(int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 11, 0);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          17,
          2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 16, 2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 18, 2);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          1,
          8);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 2, 2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 3, 1);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          4,
          2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 5, 1);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 13, 1);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          14,
          1);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 11, 1);
        break;
      case 11:
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 17, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          16,
          2);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 1, 4);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 2, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          3,
          0);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 4, 4);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 5, 2);
        (*(void (__thiscall **)(int, int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          6,
          0);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 13, 3);
        (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 14, 3);
        (*(void (__thiscall **)(int, int, _DWORD, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          0,
          11,
          0);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 17, 2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 16, 2);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          18,
          2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 1, 5);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 2, 2);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          3,
          1);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 4, 2);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 5, 1);
        (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          1,
          13,
          1);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 14, 1);
        (*(void (__stdcall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 11, 1);
        break;
      default:
        break;
    }
    switch ( rgb_modulation_selector )
    {
      case 0:
        byte_664A3C = 1;
        break;
      case 1:
        byte_664A3C = 0;
        break;
      case 2:
        byte_664A3C = 1;
        break;
      case 3:
        byte_664A3C = 1;
        break;
      case 4:
        byte_664A3C = 1;
        break;
      default:
        break;
    }
    switch ( alpha_modulation_selector )
    {
      case 0:
        byte_664A3D = 1;
        break;
      case 1:
        byte_664A3D = 1;
        break;
      case 2:
        byte_664A3D = 0;
        break;
      case 3:
        byte_664A3D = 1;
        break;
      default:
        break;
    }
    result = blend_selector;
    switch ( blend_selector )
    {
      case 0:
        result = (*(int (__thiscall **)(int, int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(
                   dword_1DAEDC4,
                   dword_1DAEDC4,
                   27,
                   0);
        break;
      case 1:
        (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 27, 1);
        (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 19, 2);
        result = (*(int (__thiscall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
                   dword_1DAEDC4,
                   dword_1DAEDC4,
                   20,
                   2);
        break;
      case 2:
      case 4:
        (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 27, 1);
        (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 19, 5);
        result = (*(int (__thiscall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
                   dword_1DAEDC4,
                   dword_1DAEDC4,
                   20,
                   2);
        break;
      case 3:
        if ( (word_1DAE83C[0] & 0x10) != 0 )
        {
          (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 27, 1);
          (*(void (__thiscall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
            dword_1DAEDC4,
            dword_1DAEDC4,
            19,
            5);
          result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 20, 6);
        }
        else
        {
          (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 27, 1);
          result = (*(int (__thiscall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
                     dword_1DAEDC4,
                     dword_1DAEDC4,
                     19,
                     12);
        }
        break;
      case 5:
        result = 0;
        if ( (word_1DAE83C[0] & 0x100) != 0 )
        {
          (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 27, 1);
          (*(void (__thiscall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
            dword_1DAEDC4,
            dword_1DAEDC4,
            19,
            9);
          result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 20, 1);
        }
        break;
      case 6:
        (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 27, 1);
        (*(void (__thiscall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          19,
          10);
        result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 20, 1);
        break;
      case 7:
        (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 27, 1);
        (*(void (__thiscall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          19,
          9);
        result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 20, 3);
        break;
      default:
        break;
    }
    switch ( depth_alpha_test_selector )
    {
      case 0:
        (*(void (__stdcall **)(int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 15, 0);
        (*(void (__stdcall **)(int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 7, 0);
        result = (*(int (__thiscall **)(int, int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(
                   dword_1DAEDC4,
                   dword_1DAEDC4,
                   14,
                   0);
        break;
      case 1:
        (*(void (__stdcall **)(int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 15, 0);
        if ( dword_187CD1C )
          (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
            dword_1DAEDC4,
            7,
            dword_187CD1C != 1 ? 0 : 2);
        else
          (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 7, 1);
        (*(void (__stdcall **)(int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 14, 0);
        result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
                   dword_1DAEDC4,
                   23,
                   dword_187CD1C != 0 ? 4 : 7);
        break;
      case 2:
        (*(void (__stdcall **)(int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 15, 0);
        if ( dword_187CD1C )
          (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
            dword_1DAEDC4,
            7,
            dword_187CD1C != 1 ? 0 : 2);
        else
          (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 7, 1);
        (*(void (__thiscall **)(int, int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          14,
          0);
        result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 23, 3);
        break;
      case 3:
        (*(void (__stdcall **)(int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 15, 0);
        (*(void (__thiscall **)(int, int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          7,
          0);
        result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 14, 1);
        break;
      case 4:
        (*(void (__stdcall **)(int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 15, 0);
        if ( dword_187CD1C )
          (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
            dword_1DAEDC4,
            7,
            dword_187CD1C != 1 ? 0 : 2);
        else
          (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 7, 1);
        (*(void (__thiscall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          14,
          1);
        result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
                   dword_1DAEDC4,
                   23,
                   dword_187CD1C != 0 ? 4 : 7);
        break;
      case 5:
        if ( dword_187CD1C )
          (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
            dword_1DAEDC4,
            7,
            dword_187CD1C != 1 ? 0 : 2);
        else
          (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 7, 1);
        (*(void (__thiscall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          14,
          1);
        (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
          dword_1DAEDC4,
          23,
          dword_187CD1C != 0 ? 4 : 7);
        (*(void (__thiscall **)(int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(
          dword_1DAEDC4,
          dword_1DAEDC4,
          15,
          1);
        (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 24, 16);
        result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 25, 7);
        break;
      default:
        break;
    }
    if ( fog_selector >= 0 )
    {
      if ( fog_selector <= 2 )
      {
        if ( byte_187CCF0 )
        {
          unk_1E014E4 = dword_664A14 == 2;
          return (*(char (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 28, 1);
        }
      }
      else if ( fog_selector != 3 )
      {
        return result;
      }
      unk_1E014E4 = 0;
      return (*(char (__thiscall **)(int, int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(
               dword_1DAEDC4,
               dword_1DAEDC4,
               28,
               0);
    }
  }
  return result;
}

