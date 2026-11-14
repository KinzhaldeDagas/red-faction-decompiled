// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00472830 rf_item_definition_register_pickup_handler
// UNREALRED VERIFIED [event-item-dispatch-20261028]: Looks up class name using0x473770. Missing returns-1. On success stores supplied callback/context dwords at definition+72/+76 (base0x6F9130 stride80), returns0. Does not validate callback or invoke it.
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Resolves supplied class name with FIRST ordinal473770. Missing returns-1; success writes callback+48 and context+4C at base6F9130+80*ID, returns0 without invoking callback. Consequently duplicate class rows after first keep default handler.
int __cdecl rf_item_definition_register_pickup_handler(char *String1, int a2, int a3)
{
  int v4; // [esp+0h] [ebp-4h]

  v4 = rf_item_definition_find_by_name(String1);
  if ( v4 == -1 )
    return -1;
  unk_6F9178[20 * v4] = a2;
  unk_6F917C[20 * v4] = a3;
  return 0;
}

