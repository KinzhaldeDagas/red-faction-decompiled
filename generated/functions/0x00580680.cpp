// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580680 rf_volume_sphere_create
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Allocates136-byte volume,invokes member no-op constructors,then stores tag1 at0,RGB bytes at1..3,strength float at4,center vector at8,radius float at20. Appends owned pointer to global array18CCFF4 and returns pointer. Remaining cached fields are not initialized here;visibility preparation fills them. No radius/strength checks. NULL allocation path still dereferences NULL;no recoverable allocation failure.
float *__cdecl rf_volume_sphere_create(float *source, float a2, float a3, char a4, char a5, char a6)
{
  char *v7; // [esp+4h] [ebp-28h]
  float copy_result[3]; // [esp+8h] [ebp-24h] BYREF
  void *v9; // [esp+14h] [ebp-18h]
  char *v10; // [esp+18h] [ebp-14h]
  char *v11; // [esp+1Ch] [ebp-10h]
  int v12; // [esp+28h] [ebp-4h]

  v9 = operator new(0x88u);
  v12 = 0;
  if ( v9 )
    v7 = rf_volume136_construct_members_noop((char *)v9);
  else
    v7 = nullptr;
  v10 = v7;
  v12 = -1;
  v11 = v7;
  *v7 = 1;
  rf_vector_copy((float *)v11 + 2, copy_result, source);
  *((float *)v11 + 5) = a2;
  *((float *)v11 + 1) = a3;
  v11[1] = a4;
  v11[2] = a5;
  v11[3] = a6;
  rf_pointer_array_append_dword(unk_18CCFF4, (int)v11);
  return (float *)v11;
}

