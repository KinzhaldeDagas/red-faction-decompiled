// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005702D0 rf_console_lexer_initialize_character_classes
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args.256DWORD table1809410:default2(single-char),digits0..9=4,ASCII A..Z/a..z=0. Additional literal indices plus43,minus45,dot46=4;underscore95,colon58,backslash92,percent37=0;double-quote34=1;NUL0=3. Sets current byte180930C=0. Percent class is normally bypassed because character advance maps percent->underscore. No locale/Unicode or whitespace classification;skip helper separately recognizes only space/tab. EAX incidental loop result.
int rf_console_lexer_initialize_character_classes()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]
  int j; // [esp+0h] [ebp-4h]
  int k; // [esp+0h] [ebp-4h]
  int m; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 256; ++i )
  {
    unk_1809410[(unsigned __int8)i] = 2;
    result = i + 1;
  }
  for ( j = 48; j <= 57; ++j )
  {
    result = (unsigned __int8)j;
    unk_1809410[(unsigned __int8)j] = 4;
  }
  for ( k = 65; k <= 90; ++k )
    unk_1809410[(unsigned __int8)k] = 0;
  for ( m = 97; m <= 122; ++m )
  {
    unk_1809410[(unsigned __int8)m] = 0;
    result = m + 1;
  }
  unk_18094C8 = 4;
  unk_18094C4 = 4;
  unk_18094BC = 4;
  unk_180958C = 0;
  unk_1809498 = 1;
  unk_1809410[0] = 3;
  unk_18094F8 = 0;
  unk_1809580 = 0;
  unk_18094A4 = 0;
  unk_180930C = 0;
  return result;
}

