// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043E740 sub_43E740
// UNREALRED VERIFIED [burn-motion-20261029]: Initializes eight 64-byte fire-owner records and a shared disarmed spread/fade deadline. Resolves Foley Burn Entity and emitter definitions humanoid fire 1 / humanoid fire 2. The owner allocator 43E970 needs a free record and binds three first-definition emitters plus one second-definition emitter.
// UNREALRED VERIFIED [combat-burn-owner-20261104]: Initializes eight64-byte fire records and ordered circular free list in ascending slot order, active empty; resolves Burn Entity Foley and humanoid fire1/fire2 definitions. Allocation consumes free head; records removed later append to free tail. Pool limit is world-global8, not per-character.
// UNREALRED CORRECTION VERIFIED [combat-burn-owner-erratum-20261104]: The earlier combat-burn-owner comment conflated initialization with reset. This function initializes eight records, disarms the shared deadline, resolves exact emitter names "humanoid fire 1" and "humanoid fire 2" plus Foley "Burn Entity", and registers43E8A0 with atexit. It does NOT build the free ring here. Raw43E8A0 performs ascending free-ring reconstruction. Earlier analysis is retained with this explicit correction.
int sub_43E740()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 8; ++i )
  {
    unk_6E6510[16 * i] = 0;
    unk_6E6514[16 * i] = 0;
    unk_6E6518[16 * i] = 0;
    unk_6E651C[16 * i] = 0;
    unk_6E6520[16 * i] = -1;
    unk_6E6524[16 * i] = -1;
    unk_6E6528[16 * i] = -1;
    unk_6E652C[16 * i] = -1;
    unk_6E6530[16 * i] = -1;
    unk_6E6534[16 * i] = -1;
    *((float *)&unk_6E6538 + 16 * i) = 1.0;
    unk_6E653C[64 * i] = 0;
    *((float *)&unk_6E6540 + 16 * i) = 0.0;
    unk_6E6548[16 * i] = 0;
    unk_6E654C[16 * i] = 0;
  }
  dword_661564 = rf_foley_definition_find_name("Burn Entity");
  rf_replicator_reset(&unk_6E6710);
  dword_661568 = rf_particle_emitter_definition_find_name("humanoid fire 1");
  dword_66156C = rf_particle_emitter_definition_find_name("humanoid fire 2");
  return atexit(sub_43E8A0);
}

