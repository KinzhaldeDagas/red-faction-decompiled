// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00558BA0 rf_face_projection_axes_select
// UNREALRED VERIFIED [trigger-airlock-20261022] Dominant-axis tie priority is Z then Y then X. Table663E68 is {2,1,0,2,1,0}; positive selected normal uses pairs(Z,Y),(X,Z),(Y,X), nonpositive swaps the pair. This axis/sign choice feeds projected odd-even containment5337E0.
// UNREALRED VERIFIED [combat-native-planes-20261104]: Projection uses RF-space normal components with dominant-axis tie order Z,Y,X. Positive selected component chooses (Z,Y),(X,Z),(Y,X) for droppedX/Y/Z; nonpositive swaps the pair. UE X/Y/Z tie order and generic FindBestAxisVectors are not equivalent after RF-to-UE axis rotation.
int __thiscall rf_face_projection_axes_select(float *this, int *a2, _DWORD *a3, int *a4)
{
  int result; // eax
  float v5; // [esp+0h] [ebp-20h]
  float v6; // [esp+4h] [ebp-1Ch]
  float v7; // [esp+8h] [ebp-18h]
  float v9; // [esp+10h] [ebp-10h] BYREF
  float v10; // [esp+14h] [ebp-Ch]
  float v11; // [esp+18h] [ebp-8h]
  float v12; // [esp+1Ch] [ebp-4h]

  rf_vector3_default_construct_noop(&v9);
  v7 = fabs(*this);
  v9 = v7;
  v6 = fabs(*(this + 1));
  v10 = v6;
  v5 = fabs(*(this + 2));
  v11 = v5;
  if ( v6 >= (double)v7 )
  {
    if ( v11 >= (double)v10 )
    {
      *a2 = 2;
      v12 = *(this + 2);
    }
    else
    {
      *a2 = 1;
      v12 = *(this + 1);
    }
  }
  else if ( v11 >= (double)v9 )
  {
    *a2 = 2;
    v12 = *(this + 2);
  }
  else
  {
    *a2 = 0;
    v12 = *this;
  }
  if ( v12 <= 0.0 )
  {
    *a3 = dword_663E6C[2 * *a2];
    result = *a2;
    *a4 = dword_663E68[2 * *a2];
  }
  else
  {
    *a3 = dword_663E68[2 * *a2];
    result = dword_663E6C[2 * *a2];
    *a4 = result;
  }
  return result;
}

