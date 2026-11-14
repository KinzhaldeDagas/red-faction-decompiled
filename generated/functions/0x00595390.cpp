// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00595390 rf_scene_point_record140_initialize_defaults
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, input remapping,text wrapping,Bink playback/default records,archive metadata,projection/aperture/classification and glass submission): Thiscall defaults for scene point-pool140-byte records constructed by596440. Writes BYTE0=0;float4 at4=(0,0,0,1),vector20=(0,0,0),float4 at32=(0,0,0,1),vector48=(0,0,0),BYTE60=0,float64=0,float68=40,BYTE72=0. Bytes1..3,61..63 and73..139 remain untouched. No allocation,whole-record clear,validation or identity matrix write;returns receiver. Does not establish a field meaning such as FOV for value40. Global initializer62E670 constructs50 records with stride140 at1BC2160.
float *__thiscall rf_scene_point_record140_initialize_defaults(float *this)
{
  float *v1; // eax
  float *v2; // eax
  float copy_result[3]; // [esp+14h] [ebp-28h] BYREF
  float v6[3]; // [esp+20h] [ebp-1Ch] BYREF
  float v7[4]; // [esp+2Ch] [ebp-10h] BYREF

  *(_BYTE *)this = 0;
  v1 = rf_float4_construct_components(v7, 0.0, 0.0, 0.0, 1.0);
  rf_float4_copy_return_destination(this + 1, v1);
  v2 = rf_vector3_set_components_return_destination(v6, 0.0, 0.0, 0.0);
  rf_vector_copy(this + 5, copy_result, v2);
  *(this + 8) = 0.0;
  *(this + 9) = 0.0;
  *(this + 10) = 0.0;
  *(this + 11) = 1.0;
  *(this + 12) = 0.0;
  *(this + 13) = 0.0;
  *(this + 14) = 0.0;
  *((_BYTE *)this + 60) = 0;
  *(this + 16) = 0.0;
  *(this + 17) = 40.0;
  *((_BYTE *)this + 72) = 0;
  return this;
}

