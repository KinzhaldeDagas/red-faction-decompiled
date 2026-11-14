// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062D920 rf_geomod_corner_pool_static_init
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native complete 10-instruction/33-byte body independently matched to original PE. No arguments. Push original tag literal g_face_vertex at0063FBC0, set ECX
// fixed pool00D65610, call verified constructor00536520(rf_geomod_corner_pool_construct); constructor RET4 consumes tag. Ignore constructor EAX, push cleanup callback0062F580, cdecl
// _atexit6060D2, caller ADD4, return registration EAX (0 on successful onexit registration, -1 on NULL failure). No own once/ready guard or rollback on registration failure. Every
// invocation reinitializes pool free-list bookkeeping per constructor contract, potentially losing previous live/spill state; registration does not prove all active nodes will be
// freed. Cleanup callback is static pool wrapper, not scalar delete of embedded pool allocation.
int rf_geomod_corner_pool_static_init()
{
  rf_geomod_corner_pool_construct(rf_geomod_corner_pool_descriptor, (int)"g_face_vertex");
  return atexit(rf_geomod_corner_pool_static_destroy);
}

