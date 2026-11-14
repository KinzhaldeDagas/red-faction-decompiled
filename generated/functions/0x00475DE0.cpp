// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00475DE0 rf_cutscene_segment_sum_duration
// UNREALRED VERIFIED [cutscene-ui-20261028]: Null record or negative segment index returns0. Otherwise sums three float fields at record+12+32*i,+16+32*i,+20+32*i and rounds through float return storage. No upper index bound; does not apply timing divisor itself.
double __cdecl rf_cutscene_segment_sum_duration(int a1, int a2)
{
  if ( !a1 || a2 < 0 )
    return 0.0;
  return (float)(*(float *)(a1 + 32 * a2 + 12) + *(float *)(a1 + 32 * a2 + 16) + *(float *)(a1 + 32 * a2 + 20));
}

