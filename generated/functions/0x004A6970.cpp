// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A6970 rf_net_statistics_record_packet
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Thiscall(stats,raw32-bit byte count,raw outgoing flag,signed opcode), native RET12. Any nonzero outgoing selects total+0, frame history+8, second history+252, opcode byte
// totals+520, opcode counts+960. Zero selects total+4, frame history+128, second history+372, opcode byte totals+740, opcode counts+1180. Adds raw32-bit byte count with native
// wrapping arithmetic. For history indices DWORD+248/+492, SIGNED index<30 writes slot[index], otherwise slot29; there is no lower-bound check for negative indices.
// Signed opcode<0 skips opcode arrays/counters. Every opcode>=0 directly indexes the selected byte-total/count arrays with no upper bound although initializer creates55 entries. Adds
// byte count and increments packet count. Opcode EXACTLY38 additionally increments stats+500 for outgoing or+504 for incoming. No mode/authority/size validation or networking; EAX is
// arithmetic/address artifact, not a reliable pointer/result.
_DWORD *__thiscall rf_net_statistics_record_packet(_DWORD *this, int a2, int a3, int a4)
{
  _DWORD *result; // eax
  _DWORD *v5; // [esp+4h] [ebp-10h]
  _DWORD *v6; // [esp+8h] [ebp-Ch]
  _DWORD *v7; // [esp+Ch] [ebp-8h]
  _DWORD *v8; // [esp+10h] [ebp-4h]

  if ( a3 )
  {
    *this += a2;
    v8 = this + 2;
    v7 = this + 63;
    v5 = this + 130;
    v6 = this + 240;
  }
  else
  {
    *(this + 1) += a2;
    v8 = this + 32;
    v7 = this + 93;
    v5 = this + 185;
    v6 = this + 295;
  }
  if ( (int)*(this + 62) < 30 )
    v8[*(this + 62)] += a2;
  else
    v8[29] += a2;
  if ( (int)*(this + 123) < 30 )
  {
    result = (_DWORD *)(a2 + v7[*(this + 123)]);
    v7[*(this + 123)] = result;
  }
  else
  {
    result = v7;
    v7[29] += a2;
  }
  if ( a4 >= 0 )
  {
    v5[a4] += a2;
    result = (_DWORD *)(v6[a4] + 1);
    v6[a4] = result;
    if ( a4 == 38 )
    {
      result = this;
      if ( a3 )
        ++*(this + 125);
      else
        ++*(this + 126);
    }
  }
  return result;
}

