// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057AE90 rf_cstring_format_angle_bracket_vector3_unbounded
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl destination, UNUSED second integer/capacity-like argument, float[3] source, precision. Promotes components to double for sprintf with exact format < %.*f, %.*f, %.*f > into68-byte local buffer, then copies including NUL to caller destination. No local-buffer or destination-capacity guard; precision passed straight to sprintf. Copy advances destination past terminating NUL and leaves that pointer in EAX before security-cookie helper; not a character count or destination base. No normalization.
char *__cdecl rf_cstring_format_angle_bracket_vector3_unbounded(
        char *out_text,
        int unused_capacity,
        const float *vector,
        int precision)
{
  char *result; // eax
  char v5; // [esp+23h] [ebp-55h]
  char *v7; // [esp+2Ch] [ebp-4Ch]
  char Buffer[68]; // [esp+30h] [ebp-48h] BYREF

  sprintf(Buffer, "< %.*f, %.*f, %.*f >", precision, *vector, precision, vector[1], precision, vector[2]);
  v7 = Buffer;
  do
  {
    v5 = *v7;
    *out_text = *v7++;
    result = ++out_text;
  }
  while ( v5 );
  return result;
}

