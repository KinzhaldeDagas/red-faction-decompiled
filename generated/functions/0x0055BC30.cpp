// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055BC30 rf_matrix3_inverse_in_place_if_nonsingular
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): Computes float determinant55B1F0. If determinant compares unequal0, computes all9adjugate entries with2x2 determinant helper567D20 into temporaries, then divides each by stored determinant and overwrites receiver. EXACT zero determinant leaves original matrix unchanged with no status. No near-singular tolerance, finite check, fallback identity or transpose assumption. Return declaration void; no failure indication.
void __thiscall rf_matrix3_inverse_in_place_if_nonsingular(float *this)
{
  float v2; // [esp+14h] [ebp-28h] BYREF
  float v3; // [esp+18h] [ebp-24h]
  float v4; // [esp+1Ch] [ebp-20h]
  float v5; // [esp+20h] [ebp-1Ch]
  float v6; // [esp+24h] [ebp-18h]
  float v7; // [esp+28h] [ebp-14h]
  float v8; // [esp+2Ch] [ebp-10h]
  float v9; // [esp+30h] [ebp-Ch]
  float v10; // [esp+34h] [ebp-8h]
  float v11; // [esp+38h] [ebp-4h]

  rf_matrix3_construct((char *)&v2);
  v11 = rf_matrix3_determinant_x87(this);
  if ( v11 != 0.0 )
  {
    v2 = rf_determinant2x2_x87(*(this + 4), *(this + 5), *(this + 7), *(this + 8));
    v3 = -rf_determinant2x2_x87(*(this + 1), *(this + 2), *(this + 7), *(this + 8));
    v4 = rf_determinant2x2_x87(*(this + 1), *(this + 2), *(this + 4), *(this + 5));
    v5 = -rf_determinant2x2_x87(*(this + 3), *(this + 5), *(this + 6), *(this + 8));
    v6 = rf_determinant2x2_x87(*this, *(this + 2), *(this + 6), *(this + 8));
    v7 = -rf_determinant2x2_x87(*this, *(this + 2), *(this + 3), *(this + 5));
    v8 = rf_determinant2x2_x87(*(this + 3), *(this + 4), *(this + 6), *(this + 7));
    v9 = -rf_determinant2x2_x87(*this, *(this + 1), *(this + 6), *(this + 7));
    v10 = rf_determinant2x2_x87(*this, *(this + 1), *(this + 3), *(this + 4));
    *this = v2 / v11;
    *(this + 1) = v3 / v11;
    *(this + 2) = v4 / v11;
    *(this + 3) = v5 / v11;
    *(this + 4) = v6 / v11;
    *(this + 5) = v7 / v11;
    *(this + 6) = v8 / v11;
    *(this + 7) = v9 / v11;
    *(this + 8) = v10 / v11;
  }
}

