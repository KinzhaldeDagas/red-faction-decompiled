// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047B080 rf_rfl_light_runtime_initialize
// VERIFIED: Initializes an RFL runtime light. Modes 3/4 start one of two intensity states, sample a randomized dwell duration with a 0.1-second floor, create the point/spot/tube renderer object, clear elapsed time, then apply the authored enabled state.
// UNREALRED VERIFIED [rfl-light-decode]: Selects initial intensity and creates the matching point, spot, or tube renderer-light representation.
int __thiscall rf_rfl_light_runtime_initialize(int this)
{
  float scalar; // [esp+30h] [ebp-64h]
  float v3; // [esp+34h] [ebp-60h]
  float v4; // [esp+38h] [ebp-5Ch]
  int v5; // [esp+3Ch] [ebp-58h]
  double v6; // [esp+40h] [ebp-54h]
  double v7; // [esp+48h] [ebp-4Ch]
  double v8; // [esp+50h] [ebp-44h]
  double v9; // [esp+58h] [ebp-3Ch]
  float sum_result[3]; // [esp+68h] [ebp-2Ch] BYREF
  float rhs[3]; // [esp+74h] [ebp-20h] BYREF
  float out_vector[3]; // [esp+80h] [ebp-14h] BYREF
  float v14; // [esp+8Ch] [ebp-8h]
  int v15; // [esp+90h] [ebp-4h]

  if ( *(int *)(this + 148) > -1 )
    rf_renderer_light_release(*(_DWORD *)(this + 148), 0);
  v14 = 1.0;
  switch ( *(_DWORD *)(this + 60) )
  {
    case 1:
      v14 = *(float *)(this + 112);
      *(_BYTE *)(this + 144) = 0;
      break;
    case 2:
      v14 = *(float *)(this + 108);
      *(_BYTE *)(this + 144) = 1;
      break;
    case 3:
      v14 = *(float *)(this + 112);
      *(_BYTE *)(this + 144) = 0;
      v7 = *(float *)(this + 124) - *(float *)(this + 128);
      v6 = *(float *)(this + 128) * 2.0;
      *(float *)(this + 136) = sub_567730() * v6 + v7;
      if ( *(float *)(this + 136) < 0.1000000014901161 )
        *(float *)(this + 136) = 0.1;
      break;
    case 4:
      v14 = *(float *)(this + 108);
      *(_BYTE *)(this + 144) = 1;
      v9 = *(float *)(this + 116) - *(float *)(this + 120);
      v8 = *(float *)(this + 120) * 2.0;
      *(float *)(this + 136) = sub_567730() * v8 + v9;
      if ( *(float *)(this + 136) < 0.1000000014901161 )
        *(float *)(this + 136) = 0.1;
      break;
    default:
      break;
  }
  if ( *(_BYTE *)(this + 133) )
    v15 = 2;
  else
    v15 = *(_BYTE *)(this + 132) != 0;
  v5 = *(_DWORD *)(this + 64);
  switch ( v5 )
  {
    case 1:
      *(_DWORD *)(this + 148) = rf_renderer_point_light_create(
                                  this + 12,
                                  *(float *)(this + 80),
                                  v14,
                                  *(float *)(this + 68),
                                  *(float *)(this + 72),
                                  *(float *)(this + 76),
                                  *(_BYTE *)(this + 134),
                                  v15,
                                  *(_DWORD *)(this + 100));
      break;
    case 2:
      v4 = (*(float *)(this + 88) + *(float *)(this + 92)) * 3.141592741012573 / 180.0;
      v3 = *(float *)(this + 88) * 3.141592741012573 / 180.0;
      *(_DWORD *)(this + 148) = rf_renderer_spot_light_create(
                                  this + 12,
                                  this + 48,
                                  v3,
                                  v4,
                                  *(float *)(this + 80),
                                  v14,
                                  *(float *)(this + 68),
                                  *(float *)(this + 72),
                                  *(float *)(this + 76),
                                  *(_BYTE *)(this + 134),
                                  v15,
                                  *(float *)(this + 96),
                                  *(_DWORD *)(this + 100),
                                  0);
      break;
    case 3:
      scalar = *(float *)(this + 104) * 0.5;
      rf_vector_multiply_scalar((const float *)(this + 24), rhs, scalar);
      rf_vector_add((const float *)(this + 12), sum_result, rhs);
      rf_vector_subtract((const float *)(this + 12), out_vector, rhs);
      *(_DWORD *)(this + 148) = rf_renderer_tube_light_create(
                                  (int)sum_result,
                                  (int)out_vector,
                                  *(float *)(this + 80),
                                  v14,
                                  *(float *)(this + 68),
                                  *(float *)(this + 72),
                                  *(float *)(this + 76),
                                  *(_BYTE *)(this + 134),
                                  v15,
                                  *(_DWORD *)(this + 100));
      break;
  }
  *(float *)(this + 140) = 0.0;
  return rf_renderer_light_set_enabled(*(_DWORD *)(this + 148), *(_BYTE *)(this + 145));
}

