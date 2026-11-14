// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00532310 sub_532310
// UNREALRED VERIFIED [particle-contact-geometry-20261104] Classifies one cutter face against the selected room's ordered face list. Ray origin is the arithmetic mean of ordered face corners; length is the selected room AABB extent sum + 0.0001. Seed is copied from the face normal initially and again before each retry; threshold starts at 0.97530001 and decreases by 0.1357900053262711 to -1. Skips the source face and metadata flags 0x04/0x08. Near-edge requests allow 15 restarts; later requests continue the current scan. Writes the resulting query class into face flag bits 28..30 and returns 1. The world argument is unused in this body; unlike 0x532BA0, this is selected-room face classification.
char __thiscall sub_532310(float *this, int a2, float *a3)
{
  int v3; // eax
  float copy_result[3]; // [esp+Ch] [ebp-70h] BYREF
  int v7; // [esp+18h] [ebp-64h]
  int i; // [esp+1Ch] [ebp-60h]
  float v9; // [esp+20h] [ebp-5Ch]
  float destination[3]; // [esp+24h] [ebp-58h] BYREF
  float v11; // [esp+30h] [ebp-4Ch]
  char v12[60]; // [esp+34h] [ebp-48h] BYREF
  int v13[3]; // [esp+70h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v13);
  rf_geomod_face_centroid(this, (float *)v13);
  v11 = a3[5] - a3[2];
  v11 = a3[6] - a3[3] + v11;
  v11 = a3[7] - a3[4] + v11;
  v11 = v11 + 0.00009999999747378752;
  ++rf_geomod_classification_attempt_count;
  v9 = 0.97530001;
  rf_geomod_face_ray_query_init(v12);
  rf_vector3_copy_return_destination(destination, this);
  sub_531CD0(destination, 0.97530001);
  rf_geomod_face_ray_query_begin((int)v12, (int)this, (float *)v13, destination, v11, 0);
  v7 = 0;
LABEL_2:
  for ( i = rf_receiver_get_first_dword(a3 + 10); i; i = rf_face_next_room_link(i) )
  {
    if ( (float *)i != this && rf_geomod_face_flags_eligible((_DWORD *)(i + 40)) )
    {
      if ( rf_geomod_face_ray_query_accumulate((int)v12, i) )
      {
        if ( ++v7 < 16 )
        {
          if ( v9 > -1.0 )
          {
            v9 = v9 - 0.1357900053262711;
            if ( v9 < -1.0 )
              v9 = -1.0;
          }
          rf_vector_copy(destination, copy_result, this);
          sub_531CD0(destination, v9);
          rf_geomod_face_ray_query_begin((int)v12, (int)this, (float *)v13, destination, v11, 0);
          ++rf_geomod_classification_retry_count;
          goto LABEL_2;
        }
      }
    }
  }
  v3 = rf_geomod_face_ray_query_class_get((int)v12);
  rf_geomod_face_boolean_class_set((int *)this + 10, v3);
  return 1;
}

