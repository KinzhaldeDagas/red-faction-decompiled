// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00602F20 rf_jpeg_prep_expand_bottom_edge
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcprepct.c:expand_bottom_edge matched): void(rowPointerArray, unsigned numCols, int inputRows, int outputRows). Copies numCols bytes from the LAST ORIGINAL row (inputRows-1) into each row inputRows..outputRows-1 using jcopy_sample_rows. No action when inputRows >= outputRows. No inputRows > 0 or capacity check. The third argument is an integer row count, not void **.
void __cdecl rf_jpeg_prep_expand_bottom_edge(
        unsigned __int8 **image_data,
        unsigned int num_cols,
        int input_rows,
        int output_rows)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = input_rows; i < output_rows; ++i )
    rf_jpeg_jcopy_sample_rows((int)image_data, input_rows - 1, (int)image_data, i, 1, num_cols);
}

