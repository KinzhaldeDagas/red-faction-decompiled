// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C810 rf_entity_definition_record52_construct_strings
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall required receiver, no stack args, plain RET; explicitly returns original receiver in EAX. Constructs empty RFStrings at0 then8. Calls CRT EH
// vector-constructor iterator6065FA(base=receiver+24,stride12,count2,ctor43C890,dtor4873C0). Verified callbacks construct/destroy ONLY each element's first8-byte RFString, so
// strings24 and36 become empty while element DWORDs32 and44, gap16..23 and trailing DWORD48 of the52-byte caller record remain untouched. No receiver allocation, full clear, scalar
// defaults, vtable store, validation or pre-existing ownership release. Iterator owns its partial-element exception cleanup; own shared2-state unwind map658928 cleans completed
// RFString8 then0, and success disables those actions before returning. Fresh EntityInfo parser contexts425240/42555E/4257FA/425BCB pass this constructor for52-byte arrays of23 or45
// records, with matching destructor43C7A0; this is an RF record constructor, not the inherited Concurrency NumaInformation identity.
void *__thiscall rf_entity_definition_record52_construct_strings(void *self)
{
  rf_string_construct_empty(self);
  rf_string_construct_empty((_DWORD *)self + 2);
  `eh vector constructor iterator'(
    (char *)self + 24,
    0xCu,
    2,
    (void (__thiscall *)(void *))rf_record_construct_first_string_empty,
    rf_glare_definition52_destroy_name_member);
  return self;
}

