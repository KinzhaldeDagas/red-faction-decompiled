// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043FCE0 rf_burn_effect_debug_draw_attachment_nodes
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): No-argument debug list procedure; EAX/AL result incidental, not success/count. Six vector locals and one
// matrix are default-constructed NO-OP ONCE before iteration, not initialized/reset per record. Start current=global active burn head6E6508; NULL ends. Each record requires all four
// DWORD emitter fields0,4,8,12 NONZERO, without handle/type validity checks; otherwise skip owner lookup/draw/release. Resolve COMMON full handle record16. Missing owner
// calls43EFD0(current,LOWBYTE0), then advances using POST-CALL record DWORD56 and LIVE global6E6508; successor was NOT cached before release. Fresh callee moves record to free
// ring6E650C and rewrites56 to free-head/self. Under valid disjoint circular active/free rings, this can enter the free ring and fail to terminate; this is a conditional
// caller/callee inference, not safe removal iteration. Other corrupt/null links retain literal behavior. Resolved owner: model128 node-transform adapter564D80 four times in order
// record node28->localA,node20->localB,node24->localC,node32->localD, sharing one matrix temporary; returns ignored, no model/node/output validity fallback. Adapter paths leaving
// output untouched can reuse uninitialized/stale ALREADY world-transformed locals from prior records. World-transform positions in order D,A,B,C by rotating with owner COMMON
// matrix72 then adding owner COMMON position60, FLOAT32 vector helper stores preserved. Draw via57EBB0(center,radius,global182ABA0): D/node32 red(255,0,0,255),A/node28
// green(0,255,0,255),C/node24 blue(0,0,255,255),B/node20 white(255,255,255,255), each radiusFLOAT0.5; finally owner COMMON position cyan(0,255,255,255), radiusFLOAT1.5. No previous
// render-color restoration. After ordinary/skip/release processing, if current56==LIVE active head then next=NULL, else next=current56, and loop; no independent count/cycle guard. No
// entity-only/death/authority/view/visibility gate or new emitter allocation.
char rf_burn_effect_debug_draw_attachment_nodes()
{
  char result; // al
  float *v1; // [esp+8h] [ebp-78h]
  _BYTE v2[12]; // [esp+Ch] [ebp-74h] BYREF
  int v3[3]; // [esp+18h] [ebp-68h] BYREF
  int v4; // [esp+24h] [ebp-5Ch]
  _BYTE v5[12]; // [esp+28h] [ebp-58h] BYREF
  char v6[36]; // [esp+34h] [ebp-4Ch] BYREF
  int v7[3]; // [esp+58h] [ebp-28h] BYREF
  int v8[3]; // [esp+64h] [ebp-1Ch] BYREF
  int v9[3]; // [esp+70h] [ebp-10h] BYREF
  float *i; // [esp+7Ch] [ebp-4h]

  rf_vector3_default_construct_noop(v9);
  rf_vector3_default_construct_noop(v8);
  rf_vector3_default_construct_noop(v2);
  rf_vector3_default_construct_noop(v5);
  rf_vector3_default_construct_noop(v7);
  rf_vector3_default_construct_noop(v3);
  rf_matrix3_construct(v6);
  result = dword_6E6508;
  for ( i = (float *)dword_6E6508; i; i = v1 )
  {
    result = (char)i;
    if ( *(_DWORD *)i )
    {
      if ( *((_DWORD *)i + 1) )
      {
        if ( *((_DWORD *)i + 2) )
        {
          result = (char)i;
          if ( *((_DWORD *)i + 3) )
          {
            v4 = rf_object_resolve_handle(*((_DWORD *)i + 4));
            if ( v4 )
            {
              rf_model_handle_get_node_transform_adapter(*(_DWORD *)(v4 + 128), (int)v7, (int)v6, *((_DWORD *)i + 7));
              rf_model_handle_get_node_transform_adapter(*(_DWORD *)(v4 + 128), (int)v9, (int)v6, *((_DWORD *)i + 5));
              rf_model_handle_get_node_transform_adapter(*(_DWORD *)(v4 + 128), (int)v8, (int)v6, *((_DWORD *)i + 6));
              rf_model_handle_get_node_transform_adapter(*(_DWORD *)(v4 + 128), (int)v3, (int)v6, *((_DWORD *)i + 8));
              rf_vector_rotate_by_matrix3((float *)v3, (float *)(v4 + 72));
              rf_vector_accumulate((float *)v3, (float *)(v4 + 60));
              rf_vector_rotate_by_matrix3((float *)v7, (float *)(v4 + 72));
              rf_vector_accumulate((float *)v7, (float *)(v4 + 60));
              rf_vector_rotate_by_matrix3((float *)v9, (float *)(v4 + 72));
              rf_vector_accumulate((float *)v9, (float *)(v4 + 60));
              rf_vector_rotate_by_matrix3((float *)v8, (float *)(v4 + 72));
              rf_vector_accumulate((float *)v8, (float *)(v4 + 60));
              rf_render_color_set_rgba8(255, 0, 0, 255);
              rf_debug_draw_wire_sphere_backend_dispatch((int)v3, 0.5, dword_182ABA0);
              rf_render_color_set_rgba8(0, 255, 0, 255);
              rf_debug_draw_wire_sphere_backend_dispatch((int)v7, 0.5, dword_182ABA0);
              rf_render_color_set_rgba8(0, 0, 255, 255);
              rf_debug_draw_wire_sphere_backend_dispatch((int)v8, 0.5, dword_182ABA0);
              rf_render_color_set_rgba8(255, 255, 255, 255);
              rf_debug_draw_wire_sphere_backend_dispatch((int)v9, 0.5, dword_182ABA0);
              rf_render_color_set_rgba8(0, 255, 255, 255);
              result = rf_debug_draw_wire_sphere_backend_dispatch(v4 + 60, 1.5, dword_182ABA0);
            }
            else
            {
              result = (unsigned __int8)rf_burn_effect_release_record(i, 0);
            }
          }
        }
      }
    }
    if ( *((_DWORD *)i + 14) == dword_6E6508 )
    {
      v1 = nullptr;
    }
    else
    {
      result = (char)i;
      v1 = *((float **)i + 14);
    }
  }
  return result;
}

