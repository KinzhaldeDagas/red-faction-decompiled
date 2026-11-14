// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048B280 rf_mover_detach_linked_object
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mover UID and handle queries, detachment and member ownership, original console packet serialization, native team-byte sentinel and authority comparisons): 
// Cdecl(mover,object), no-op if eitherNULL. Scans mover handle array704 using dynamic signed count. For EVERY slot matching object handleDWORD44, writes-1 to that slot AND same-index
// authored-link array680; no count decrement, erase or parallel-array bounds check. Copies object's published position60 to local vector, copies it into predicted240, then publishes
// that vector through position/bounds delegate (also installs current228); zeros vector324. Does not stop after first match, free object, remove array slots, clear other flags or
// modify array716. Object need not be independently resolved or type-validated here. Normal void return.
void __cdecl rf_mover_detach_linked_object(int a1, int a2)
{
  int first_dword; // eax
  float v3[3]; // [esp+0h] [ebp-28h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-1Ch] BYREF
  float destination[3]; // [esp+18h] [ebp-10h] BYREF
  int i; // [esp+24h] [ebp-4h]

  if ( a1 && a2 )
  {
    rf_vector3_default_construct_noop(destination);
    for ( i = 0; ; ++i )
    {
      first_dword = rf_receiver_get_first_dword((void *)(a1 + 704));
      if ( i >= first_dword )
        break;
      if ( *(_DWORD *)sub_552200((_DWORD *)(a1 + 704), i) == *(_DWORD *)(a2 + 44) )
      {
        *(_DWORD *)sub_552200((_DWORD *)(a1 + 704), i) = -1;
        *(_DWORD *)sub_552200((_DWORD *)(a1 + 680), i) = -1;
        rf_vector_copy(destination, copy_result, (const float *)(a2 + 60));
        rf_vector_copy((float *)(a2 + 240), v3, destination);
        rf_object_publish_position_and_bounds(a2, destination);
        rf_vector3_zero_return_destination((float *)(a2 + 324));
      }
    }
  }
}

