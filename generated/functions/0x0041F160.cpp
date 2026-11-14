// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041F160 rf_snapshot_unpack_quaternion_s16
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Destination four-float object inECX, source four signed16 words. Each multiplies exact literal0.00006103888154029846, rounds through float local and stores component. No normalization or square-root reconstruction. This is the decoder paired with0x5846A0; neighboring0x41F100 is a six-float copy, not encoder.
__int16 *__thiscall rf_snapshot_unpack_quaternion_s16(float *this, __int16 *a2)
{
  float v3; // [esp+0h] [ebp-24h]
  float v4; // [esp+8h] [ebp-1Ch]
  float v5; // [esp+10h] [ebp-14h]
  float v6; // [esp+18h] [ebp-Ch]

  v6 = (double)*a2 * 0.00006103888154029846;
  *this = v6;
  v5 = (double)a2[1] * 0.00006103888154029846;
  *(this + 1) = v5;
  v4 = (double)a2[2] * 0.00006103888154029846;
  *(this + 2) = v4;
  v3 = (double)a2[3] * 0.00006103888154029846;
  *(this + 3) = v3;
  return a2;
}

