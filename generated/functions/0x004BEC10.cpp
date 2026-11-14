// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BEC10 rf_collision_pair_should_skip
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, ordered object-pair type matrix, side-specific INOUT mask writes, native x87 unordered branches and projectile global-plane gate): 
// Cdecl(A,B,Fptr), AL1=SKIP, AL0=ADMIT. F=*Fptr is IN/OUT: never reset at entry. In the rules below '=' OVERWRITES F, '|=' preserves prior bits, and all unmentioned ordered pairs
// SKIP. Early gates: same pointer or either NULL skips; requires (A.physicsFlags424|B.physicsFlags424)&0x20; common flags124 mask0x40000 on either object skips unless the OTHER type
// is2; if BOTH MP byte704E81 and split-screen byte7B25D0 are0, any common mask0x4000 skips. No universal common delete-mask2 test or corpse-protection test. Nonnull class/F pointers
// are assumed where read/written; no finite validation or object/global/list writes apart from F.
// Notation: types E0,I1,P2,D3,Cl4,T5,Co7; type6 and>=8 skip. pl(X)=direct common124 mask8, veh(X)=shared Use==1, attachedVeh(E)=436A80 association predicate, ownerPl(P)=resolve
// common owner48 then direct mask8. gate(P,X)=4BFAC0(P,X,1). special(P)=projectile class DWORD616 mask0x20. r(X)=physical outer radius384; R(X)=common radius120. G(x,y) and L(x,y)
// mean STRICT ORDERED > and <: any NaN operand makes them false. All .05 thresholds are DOUBLE0.05000000074505806 and .2 is DOUBLE0.2000000029802322. Products2*r stay in x87 through
// comparison, with no intermediate binary32 store.
// BEFORE B dispatch, every admitted-preamble A.type2 with special(A) does F=1, even if a later branch SKIPS. Other orientations assign special-projectile bit only at the places
// stated; do not make the filter commutative or clear F on rejection.
// E/E, A is player: B mask0x20000 skips. If veh(B) OR G(rB,2*rA), ADMIT and assign F=4 EXCEPT case-insensitive common RFString24 equal Sea_Creature suppresses ONLY assignment (still
// admits). Otherwise L(rA,2*rB) admits F=0x20; else skip. This A-player branch has priority even when B is also player.
// E/E, A nonplayer/B player: A mask0x20000 skips. veh(A) OR G(rA,2*rB) admits F=2 except same Sea_Creature assignment exemption; otherwise L(rA,2*rB) admits F=0x20, else skip. These
// ordered ratio expressions differ from the A-player branch; boundary/equality/small-body behavior is asymmetric.
// E/E, neither player: either veh admits unchanged F. Otherwise W(X)=AI block X+672 primary-weapon flag20 with no secondary (40B690). Both W true admits; exactly one W true skips.
// With neither W, admits only when BOTH physics flags424 have0x40 AND NOT(L(rA,2) AND L(rB,2)); thus unordered radii can admit on this particular branch. No radius clamp or
// dead-state test.
// E/I and I/E: if MP,split-screen OR BYTE7B25D1 nonzero, ADMIT exactly when entity-dead predicate433F60 is false. With all three zero, ADMIT exactly when entity has direct player
// flag. F unchanged; extra byte7B25D1 does not bypass the earlier hidden-mask gate.
// E/P: attachedVeh(E), entity.handle44==projectile.owner48, or gate false skips with F unchanged. After passing, special(P) does F=1; ownerPl(P) does F|=2; admit. P/E uses same
// rejection conditions but has A-projectile F=1 BEFORE them; ownerPl(P) adds4 only on admission.
// E/D and D/E: ADMIT iff G(rD,.5) AND ((pl(E) AND D.solid660!=0) OR veh(E)). Only pl(E)+nonnull solid+G(rD,1) adds side bit: E/D F|=0x10, D/E F|=8. NaN radius skips, including
// vehicle cases. No bit1 assignment here.
// E/Cl and Cl/E: player entity skips its own clutter when Cl.owner48==E.handle44; otherwise G(rCl,.5) admits with F=4 for E/Cl, F=2 for Cl/E. Nonplayer entity admits only veh(E) AND
// G(rCl,.5), unchanged F; owner-equality exclusion is not tested on that nonplayer branch.
// E/T and T/E admit iff trigger filter4BFBE0(T,E) is nonzero, unchanged F. E/Co and Co/E admit iff pl(E) AND corpse physical flags424 mask0x40 set; F=4 for E/Co, F=2 for Co/E. Corpse
// flags668 protection/retirement and size are not tested there.
// P/P: A class-index664 equal global911C78 has priority: gate(B,A) true admits F|=2. Otherwise B class-index equal that global allows gate(A,B) true admission F|=4. Other cases skip;
// both-special case takes A priority. A special(P) preassignment may already have changed F on rejection.
// P/D: require nonnull D.solid660 and gate(P,D), then ALWAYS F=1 even when special(P) false. G(rD,.5) admits F|=0x10; otherwise G(rD,.05) admits unchanged; else skip, retaining F=1.
// D/P instead assigns F=1 ONLY if special(P) AFTER gate, large rD adds8 instead of0x10, and uses same ordered thresholds. NaN fails both, so pseudocode unordered else-large
// interpretation is wrong.
// P/Cl and Cl/P: only when Cl.classIndex664==global666B64, skip equal owners P48==Cl48 or nonnull resolved Cl.owner with association512==P.owner48. Then require gate(P,Cl). Cl/P
// assigns F=1 only when special(P) at this point; P/Cl already used projectile preassignment. G(rCl,.2) admits with side OR4 for P/Cl or OR2 for Cl/P. Otherwise G(rCl,0) AND
// ownerPl(P) admits unchanged; else skip. NaN skips; no logical unordered inversion of <= bounds.
// P/T and T/P admit only ownerPl(P) AND trigger flags688 mask2 AND gate(P,T). P/T keeps preassigned special bit; T/P has NO special-projectile F=1 assignment, even on admission.
// P/Co and Co/P require gate(P,Co). P/Co admits iff G(COMMON R(Co),1.5) OR ownerPl(P), then F|=4. Co/P first does F=1 if special(P), then tests PHYSICAL r(Co) instead and adds2 on
// admission. This120-versus384 operand asymmetry is native. Owner-player branch can admit NaN radius; nonplayer owner cannot.
// D/Cl ADMIT unchanged F after preamble, but reverse Cl/D SKIPS. All other type pairs skip. Trigger/projectile, corpse/projectile, helper-facing, and primary-weapon decisions use
// distinct predicates; output writes can survive rejection. Caller4BEB80 supplies initialized local F=0 and discards it on SKIP, but this routine itself promises neither
// initialization nor rollback.
bool __cdecl rf_collision_pair_should_skip(int a1, int a2, _DWORD *a3)
{
  bool result; // al
  int v4; // eax
  int v5; // eax
  int v6; // [esp+0h] [ebp-28h]
  int v7; // [esp+4h] [ebp-24h]
  int v8; // [esp+8h] [ebp-20h]
  int v9; // [esp+Ch] [ebp-1Ch]
  int v10; // [esp+20h] [ebp-8h]
  int v11; // [esp+24h] [ebp-4h]

  if ( a1 == a2 )
    return 1;
  if ( !a1 || !a2 )
    return 1;
  if ( ((*(_DWORD *)(a2 + 424) | *(_DWORD *)(a1 + 424)) & 0x20) == 0 )
    return 1;
  if ( (*(_DWORD *)(a1 + 124) & 0x40000) != 0 && *(_DWORD *)(a2 + 36) != 2 )
    return 1;
  if ( (*(_DWORD *)(a2 + 124) & 0x40000) != 0 && *(_DWORD *)(a1 + 36) != 2 )
    return 1;
  if ( !(rf_splitscreen_runtime_active | rf_multiplayer_runtime_mode)
    && ((*(_DWORD *)(a2 + 124) | *(_DWORD *)(a1 + 124)) & 0x4000) != 0 )
  {
    return 1;
  }
  switch ( *(_DWORD *)(a1 + 36) )
  {
    case 0:
      switch ( *(_DWORD *)(a2 + 36) )
      {
        case 0:
          if ( rf_object_has_player_flag(a1) )
          {
            if ( (*(_DWORD *)(a2 + 124) & 0x20000) == 0 )
            {
              if ( rf_object_is_use_vehicle((_DWORD *)a2) || *(float *)(a2 + 384) > *(float *)(a1 + 384) * 2.0 )
              {
                if ( rf_rf_string_not_equals_cstring_case_insensitive(a2 + 24, "Sea_Creature") )
                  *a3 = 4;
                return 0;
              }
              if ( *(float *)(a1 + 384) < *(float *)(a2 + 384) * 2.0 )
              {
                *a3 = 32;
                return 0;
              }
            }
            return 1;
          }
          if ( !rf_object_has_player_flag(a2) )
          {
            if ( rf_object_is_use_vehicle((_DWORD *)a1) || rf_object_is_use_vehicle((_DWORD *)a2) )
              return 0;
            if ( rf_ai_primary_flag20_without_secondary(a1 + 672) )
              return !rf_ai_primary_flag20_without_secondary(a2 + 672);
            if ( rf_ai_primary_flag20_without_secondary(a2 + 672) )
              return 1;
            return (*(_DWORD *)(a2 + 424) & *(_DWORD *)(a1 + 424) & 0x40) == 0
                || *(float *)(a1 + 384) < 2.0 && *(float *)(a2 + 384) < 2.0;
          }
          if ( (*(_DWORD *)(a1 + 124) & 0x20000) != 0 )
            return 1;
          if ( !rf_object_is_use_vehicle((_DWORD *)a1) && *(float *)(a1 + 384) <= *(float *)(a2 + 384) * 2.0 )
          {
            if ( *(float *)(a1 + 384) < *(float *)(a2 + 384) * 2.0 )
            {
              *a3 = 32;
              return 0;
            }
            return 1;
          }
          if ( rf_rf_string_not_equals_cstring_case_insensitive(a1 + 24, "Sea_Creature") )
            *a3 = 2;
          return 0;
        case 1:
          if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active || unk_7B25D1 )
            return rf_entity_is_dead(a1);
          else
            return !rf_object_has_player_flag(a1);
        case 2:
          if ( rf_entity_has_attached_use_vehicle(a1) )
            return 1;
          if ( *(_DWORD *)(a1 + 44) == *(_DWORD *)(a2 + 48) )
            return 1;
          if ( !rf_projectile_target_passes_pair_gate(a2, a1, 1) )
            return 1;
          if ( (*(_DWORD *)(*(_DWORD *)(a2 + 660) + 616) & 0x20) != 0 )
            *a3 = 1;
          v4 = rf_object_resolve_handle(*(_DWORD *)(a2 + 48));
          if ( rf_object_has_player_flag(v4) )
            *a3 |= 2u;
          return 0;
        case 3:
          if ( rf_object_has_player_flag(a1) && *(_DWORD *)(a2 + 660) )
          {
            if ( *(float *)(a2 + 384) > 1.0 )
              *a3 |= 0x10u;
            if ( *(float *)(a2 + 384) > 0.5 )
              return 0;
          }
          return !rf_object_is_use_vehicle((_DWORD *)a1) || *(float *)(a2 + 384) <= 0.5;
        case 4:
          if ( !rf_object_has_player_flag(a1) )
            return !rf_object_is_use_vehicle((_DWORD *)a1) || *(float *)(a2 + 384) <= 0.5;
          if ( *(_DWORD *)(a2 + 48) == *(_DWORD *)(a1 + 44) )
            return 1;
          if ( *(float *)(a2 + 384) <= 0.5 )
            return !rf_object_is_use_vehicle((_DWORD *)a1) || *(float *)(a2 + 384) <= 0.5;
          *a3 = 4;
          return 0;
        case 5:
          return rf_trigger_collision_pair_filter(a2, a1) == 0;
        case 7:
          if ( !rf_object_has_player_flag(a1) || (*(_DWORD *)(a2 + 424) & 0x40) == 0 )
            return 1;
          *a3 = 4;
          return 0;
        default:
          return 1;
      }
    case 1:
      if ( *(_DWORD *)(a2 + 36) )
        return 1;
      if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active || unk_7B25D1 )
        return rf_entity_is_dead(a2);
      return !rf_object_has_player_flag(a2);
    case 2:
      if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 616) & 0x20) != 0 )
        *a3 = 1;
      switch ( *(_DWORD *)(a2 + 36) )
      {
        case 0:
          if ( rf_entity_has_attached_use_vehicle(a2) )
          {
            result = 1;
          }
          else if ( *(_DWORD *)(a2 + 44) == *(_DWORD *)(a1 + 48) )
          {
            result = 1;
          }
          else if ( rf_projectile_target_passes_pair_gate(a1, a2, 1) )
          {
            v5 = rf_object_resolve_handle(*(_DWORD *)(a1 + 48));
            if ( rf_object_has_player_flag(v5) )
              *a3 |= 4u;
            result = 0;
          }
          else
          {
            result = 1;
          }
          break;
        case 2:
          if ( *(_DWORD *)(a1 + 664) == dword_911C78 )
          {
            if ( rf_projectile_target_passes_pair_gate(a2, a1, 1) )
            {
              *a3 |= 2u;
              result = 0;
            }
            else
            {
              result = 1;
            }
          }
          else if ( *(_DWORD *)(a2 + 664) == dword_911C78 )
          {
            if ( rf_projectile_target_passes_pair_gate(a1, a2, 1) )
            {
              *a3 |= 4u;
              result = 0;
            }
            else
            {
              result = 1;
            }
          }
          else
          {
            result = 1;
          }
          break;
        case 3:
          if ( *(_DWORD *)(a2 + 660) )
          {
            if ( rf_projectile_target_passes_pair_gate(a1, a2, 1) )
            {
              *a3 = 1;
              if ( *(float *)(a2 + 384) <= 0.5 )
              {
                result = *(float *)(a2 + 384) <= 0.05000000074505806;
              }
              else
              {
                *a3 |= 0x10u;
                result = 0;
              }
            }
            else
            {
              result = 1;
            }
          }
          else
          {
            result = 1;
          }
          break;
        case 4:
          if ( *(_DWORD *)(a2 + 664) != unk_666B64 )
            goto LABEL_231;
          if ( *(_DWORD *)(a1 + 48) == *(_DWORD *)(a2 + 48) )
            return 1;
          v11 = rf_object_resolve_handle(*(_DWORD *)(a2 + 48));
          if ( v11 && *(_DWORD *)(v11 + 512) == *(_DWORD *)(a1 + 48) )
          {
            result = 1;
          }
          else
          {
LABEL_231:
            if ( rf_projectile_target_passes_pair_gate(a1, a2, 1) )
            {
              if ( *(float *)(a2 + 384) <= 0.2000000029802322 )
              {
                result = *(float *)(a2 + 384) <= 0.0 || !rf_object_handle_has_direct_player_flag(*(_DWORD *)(a1 + 48));
              }
              else
              {
                *a3 |= 4u;
                result = 0;
              }
            }
            else
            {
              result = 1;
            }
          }
          break;
        case 5:
          result = !rf_object_handle_has_direct_player_flag(*(_DWORD *)(a1 + 48))
                || (*(_DWORD *)(a2 + 688) & 2) == 0
                || rf_projectile_target_passes_pair_gate(a1, a2, 1) == 0;
          break;
        case 7:
          if ( rf_projectile_target_passes_pair_gate(a1, a2, 1) )
          {
            if ( *(float *)(a2 + 120) > 1.5 || rf_object_handle_has_direct_player_flag(*(_DWORD *)(a1 + 48)) )
            {
              *a3 |= 4u;
              result = 0;
            }
            else
            {
              result = 1;
            }
          }
          else
          {
            result = 1;
          }
          break;
        default:
          result = 1;
          break;
      }
      return result;
    case 3:
      v9 = *(_DWORD *)(a2 + 36);
      if ( v9 )
      {
        if ( v9 == 2 )
        {
          if ( *(_DWORD *)(a1 + 660) )
          {
            if ( rf_projectile_target_passes_pair_gate(a2, a1, 1) )
            {
              if ( (*(_DWORD *)(*(_DWORD *)(a2 + 660) + 616) & 0x20) != 0 )
                *a3 = 1;
              if ( *(float *)(a1 + 384) <= 0.5 )
              {
                return *(float *)(a1 + 384) <= 0.05000000074505806;
              }
              else
              {
                *a3 |= 8u;
                return 0;
              }
            }
            else
            {
              return 1;
            }
          }
          else
          {
            return 1;
          }
        }
        else
        {
          return v9 != 4;
        }
      }
      else
      {
        if ( !rf_object_has_player_flag(a2) || !*(_DWORD *)(a1 + 660) )
          return !rf_object_is_use_vehicle((_DWORD *)a2) || *(float *)(a1 + 384) <= 0.5;
        if ( *(float *)(a1 + 384) > 1.0 )
          *a3 |= 8u;
        return *(float *)(a1 + 384) <= 0.5 && (!rf_object_is_use_vehicle((_DWORD *)a2) || *(float *)(a1 + 384) <= 0.5);
      }
    case 4:
      v8 = *(_DWORD *)(a2 + 36);
      if ( v8 )
      {
        if ( v8 == 2 )
        {
          if ( *(_DWORD *)(a1 + 664) != unk_666B64 )
            goto LABEL_232;
          if ( *(_DWORD *)(a1 + 48) == *(_DWORD *)(a2 + 48) )
            return 1;
          v10 = rf_object_resolve_handle(*(_DWORD *)(a1 + 48));
          if ( v10 && *(_DWORD *)(v10 + 512) == *(_DWORD *)(a2 + 48) )
          {
            return 1;
          }
          else
          {
LABEL_232:
            if ( rf_projectile_target_passes_pair_gate(a2, a1, 1) )
            {
              if ( (*(_DWORD *)(*(_DWORD *)(a2 + 660) + 616) & 0x20) != 0 )
                *a3 = 1;
              if ( *(float *)(a1 + 384) <= 0.2000000029802322 )
              {
                return *(float *)(a1 + 384) <= 0.0 || !rf_object_handle_has_direct_player_flag(*(_DWORD *)(a2 + 48));
              }
              else
              {
                *a3 |= 2u;
                return 0;
              }
            }
            else
            {
              return 1;
            }
          }
        }
        else
        {
          return 1;
        }
      }
      else
      {
        if ( !rf_object_has_player_flag(a2) )
          return !rf_object_is_use_vehicle((_DWORD *)a2) || *(float *)(a1 + 384) <= 0.5;
        if ( *(_DWORD *)(a1 + 48) == *(_DWORD *)(a2 + 44) )
          return 1;
        if ( *(float *)(a1 + 384) > 0.5 )
        {
          *a3 = 2;
          return 0;
        }
        else
        {
          return !rf_object_is_use_vehicle((_DWORD *)a2) || *(float *)(a1 + 384) <= 0.5;
        }
      }
    case 5:
      v7 = *(_DWORD *)(a2 + 36);
      if ( !v7 )
        return rf_trigger_collision_pair_filter(a1, a2) == 0;
      if ( v7 != 2 )
        return 1;
      if ( rf_object_handle_has_direct_player_flag(*(_DWORD *)(a2 + 48)) && (*(_DWORD *)(a1 + 688) & 2) != 0 )
        return rf_projectile_target_passes_pair_gate(a2, a1, 1) == 0;
      return 1;
    case 6:
      return 1;
    case 7:
      v6 = *(_DWORD *)(a2 + 36);
      if ( v6 )
      {
        if ( v6 == 2 )
        {
          if ( rf_projectile_target_passes_pair_gate(a2, a1, 1) )
          {
            if ( (*(_DWORD *)(*(_DWORD *)(a2 + 660) + 616) & 0x20) != 0 )
              *a3 = 1;
            if ( *(float *)(a1 + 384) > 1.5 || rf_object_handle_has_direct_player_flag(*(_DWORD *)(a2 + 48)) )
            {
              *a3 |= 2u;
              return 0;
            }
            else
            {
              return 1;
            }
          }
          else
          {
            return 1;
          }
        }
        else
        {
          return 1;
        }
      }
      else if ( rf_object_has_player_flag(a2) && (*(_DWORD *)(a1 + 424) & 0x40) != 0 )
      {
        *a3 = 2;
        return 0;
      }
      else
      {
        return 1;
      }
    default:
      return 1;
  }
}

