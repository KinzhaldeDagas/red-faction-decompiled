// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00490A60 rf_lag_compensation_add_entity_sample
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Cdecl(entity pointer,query time rawWORD),one32-bit argument slot for time. Signed count754150<32 admits424-byte slot754158+424*count; no count>=0/entity/bufferNULL guard or
// duplicate-handle suppression. Stores entity full handle44 atslot0,model handle128 atslot4. Calls buffered Euler sampler stdcall(entity,uint16
// time,outMatrix=slot20,tempEuler,tempOffset),then position sampler stdcall(entity,uint16 time,outPosition=slot8,tempVelocity). Native MOVZX zero-extends suppliedWORD; incidental ECX
// load of buffer632 is not a thiscall parameter in verified stdcall signatures. Sampling outputs,not query time,retained. Increments count only after samplers; normal return new
// count. At count>=32 no write and EAX incidental,not defined failure status. No physical snapshot until490B20.
int __cdecl rf_lag_compensation_add_entity_sample(int a1, __int16 a2)
{
  int result; // eax
  int *v3; // [esp+0h] [ebp-28h]
  float v4[3]; // [esp+4h] [ebp-24h] BYREF
  float v5[3]; // [esp+10h] [ebp-18h] BYREF
  float v6[3]; // [esp+1Ch] [ebp-Ch] BYREF

  if ( unk_754150 < 32 )
  {
    v3 = &unk_754158[106 * unk_754150];
    *v3 = *(_DWORD *)(a1 + 44);
    v3[1] = *(_DWORD *)(a1 + 128);
    rf_vector3_default_construct_noop(v5);
    rf_vector3_default_construct_noop(v6);
    rf_vector3_default_construct_noop(v4);
    rf_entity_sample_buffered_euler_and_offset(a1, a2, (int)(v3 + 5), v5, v6);
    rf_entity_sample_buffered_position_and_velocity(a1, a2, (float *)v3 + 2, v4);
    return ++unk_754150;
  }
  return result;
}

