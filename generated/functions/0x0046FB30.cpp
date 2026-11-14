// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046FB30 rf_text_tokenize_newline_pointers
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): cdecl(mutableText,outputPointers,count). ALWAYS writes output[0]=strtok(text,"\n") BEFORE count check, even count<=0. For i=1 while signed i<count, if previous token nonnull
// stores strtok(NULL,"\n"), otherwise storesNULL. EAX returns terminal i (1 when count<=1), not actual nonnull-token count. Original delimiters are newline only; repeated/leading
// delimiters follow CRT strtok behavior, CR is not explicitly stripped. Source is modified, outputs point into source; no destination/null/count validation or private tokenizer
// state.
int __cdecl rf_text_tokenize_newline_pointers(char *String, char **a2, int a3)
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  *a2 = strtok(String, "\n");
  for ( i = 1; ; ++i )
  {
    result = i;
    if ( i >= a3 )
      break;
    if ( a2[i - 1] )
      a2[i] = strtok(nullptr, "\n");
    else
      a2[i] = nullptr;
  }
  return result;
}

