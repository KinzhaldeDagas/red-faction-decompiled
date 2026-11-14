// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040DE20 rf_ai_publish_owner_route_search_request
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(required ENTITY pointer); embedded route=owner+1416. Publishes mutable SHARED request at6663FC, without NULL/reentrancy
// guards or own route reset. FLOAT owner+1984/+1988 ->request+24/+28. Calls40B6D0(owner+672), stores returned AL VERBATIM atrequest+33. Movement predicate437F60(owner) any nonzero,
// otherwise437FD0(owner) any nonzero, sets route DWORD+92=1 and request BYTE+32=0; both zero set route+92=0/request+32=1. Predicates inspect current descriptor
// categories12,15,13,11,9 and4,7 respectively; second call short-circuited. Copies owner COMMON position+60 sequentially into route vectors+28 and+40 via thiscall assignment; stack
// result vectors are temporary copies, not persistent destinations. Request+0=route+28, +4=route DWORD+276(owner+1692), +8=route DWORD+280(owner+1696), FLOAT+40=0,+44=0,+36=current
// world-solid pointer,+56=route+4 output storage pointer. Does NOT clear request+48 cost or+52 result count here. Full EAX at return is copied owner DWORD+1696, not Boolean success;
// callers discard it. No allocation, path search, target resolution, owner destination+1772 write or output-buffer capacity validation in this body.
int __cdecl rf_ai_publish_owner_route_search_request(float *a1)
{
  int result; // eax
  float v2[3]; // [esp+0h] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-10h] BYREF
  float *v4; // [esp+18h] [ebp-4h]

  v4 = a1 + 354;
  unk_666414 = a1[496];
  unk_666418 = a1[497];
  unk_66641D = sub_40B6D0((int *)a1 + 168);
  if ( rf_entity_descriptor_mode_is_12_15_13_11_or9((int)a1) || rf_entity_movement_is_index4_or7((int)a1) )
  {
    *((_DWORD *)v4 + 23) = 1;
    unk_66641C = 0;
  }
  else
  {
    v4[23] = 0.0;
    unk_66641C = 1;
  }
  rf_vector_copy(v4 + 7, copy_result, a1 + 15);
  rf_vector_copy(v4 + 10, v2, a1 + 15);
  dword_6663FC = (int)(v4 + 7);
  unk_666424 = 0.0;
  unk_666400 = *((_DWORD *)v4 + 69);
  result = *((_DWORD *)v4 + 70);
  unk_666404 = result;
  unk_666428 = 0.0;
  unk_666420 = rf_world_solid;
  unk_666434 = v4 + 1;
  return result;
}

