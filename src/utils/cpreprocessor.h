#ifndef CPREPROCESSOR_H_
#define CPREPROCESSOR_H_

#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define EMPTY()
#define DEFER(id) id EMPTY()
#define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()
#define EXPAND(...) __VA_ARGS__

#define CHECK_N(x, n, ...) n
#define CHECK(...) CHECK_N(__VA_ARGS__, 0,)
#define PROBE(x) x, 1,

#define NOT(x) CHECK(PRIMITIVE_CAT(NOT_ , x))
#define NOT_0 PROBE(~)

#define COMPL(b) PRIMITIVE_CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

#define BOOL(x) COMPL(NOT(x))

#define FIRST(a, ...) a

#define HAS_ARGS(...) BOOL(FIRST(DEFER1(_END_OF_ARGUMENTS_) __VA_ARGS__)())
#define _END_OF_ARGUMENTS_() 0

#define EVAL_(e, ...) EVAL2(PRIMITIVE_CAT(EVAL, e) (__VA_ARGS__))
#define EVAL1(...) __VA_ARGS__

#define DEFER1(m) m EMPTY()
#define DEFER2(m) m EMPTY EMPTY()()
#define DEFER3(m) m EMPTY EMPTY EMPTY()()()
#define DEFER4(m) m EMPTY EMPTY EMPTY EMPTY()()()()

#define IF_ELSE(condition) _IF_ELSE(BOOL(condition))
#define _IF_ELSE(condition) CAT(_IF_, condition)

#define _IF_1(...) __VA_ARGS__ _IF_1_ELSE
#define _IF_0(...)             _IF_0_ELSE

#define _IF_1_ELSE(...)
#define _IF_0_ELSE(...) __VA_ARGS__

#define INC(v) PRIMITIVE_CAT(INC_, v)
#define MUL(v) PRIMITIVE_CAT(MUL_, v)

#define PP_NARG(...) \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...) \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

template <unsigned I = 0>
struct compile_time_counter {
  static constexpr unsigned value = I;
};

#define MAP(m, k, index, first, ...)           \
  m(index, k, first)                           \
  IF_ELSE(HAS_ARGS(__VA_ARGS__))(    \
    DEFER2(_MAP)()(m, k, INC(index), __VA_ARGS__)   \
  )(                                 \
    /* Do nothing, just terminate */ \
  )
#define _MAP() MAP

#define VA_ITER(x, k, ...) EVAL1(EXPAND EVAL_(EVAL1(PP_NARG(__VA_ARGS__)), (MAP(x, k, 0, __VA_ARGS__))))

#define INC_0 1
#define INC_1 2
#define INC_2 3
#define INC_3 4
#define INC_4 5
#define INC_5 6
#define INC_6 7
#define INC_7 8
#define INC_8 9
#define INC_9 10
#define INC_10 11
#define INC_11 12
#define INC_12 13
#define INC_13 14
#define INC_14 15
#define INC_15 16
#define INC_16 17
#define INC_17 18
#define INC_18 19
#define INC_19 20
#define INC_20 21
#define INC_21 22
#define INC_22 23
#define INC_23 24
#define INC_24 25
#define INC_25 26
#define INC_26 27
#define INC_27 28
#define INC_28 29
#define INC_29 30
#define INC_30 31
#define INC_31 32
#define INC_32 33
#define INC_33 34
#define INC_34 35
#define INC_35 36
#define INC_36 37
#define INC_37 38
#define INC_38 39
#define INC_39 40
#define INC_40 41
#define INC_41 42
#define INC_42 43
#define INC_43 44
#define INC_44 45
#define INC_45 46
#define INC_46 47
#define INC_47 48
#define INC_48 49
#define INC_49 50
#define INC_50 51
#define INC_51 52
#define INC_52 53
#define INC_53 54
#define INC_54 55
#define INC_55 56
#define INC_56 57
#define INC_57 58
#define INC_58 59
#define INC_59 60
#define INC_60 61
#define INC_61 62
#define INC_62 63
#define INC_63 64
#define INC_64 65
#define INC_65 66
#define INC_66 67
#define INC_67 68
#define INC_68 69
#define INC_69 70
#define INC_70 71
#define INC_71 72
#define INC_72 73
#define INC_73 74
#define INC_74 75
#define INC_75 76
#define INC_76 77
#define INC_77 78
#define INC_78 79
#define INC_79 80
#define INC_80 81
#define INC_81 82
#define INC_82 83
#define INC_83 84
#define INC_84 85
#define INC_85 86
#define INC_86 87
#define INC_87 88
#define INC_88 89
#define INC_89 90
#define INC_90 91
#define INC_91 92
#define INC_92 93
#define INC_93 94
#define INC_94 95
#define INC_95 96
#define INC_96 97
#define INC_97 98
#define INC_98 99
#define INC_99 100
#define INC_100 101
#define INC_101 102
#define INC_102 103
#define INC_103 104
#define INC_104 105
#define INC_105 106
#define INC_106 107
#define INC_107 108
#define INC_108 109
#define INC_109 110
#define INC_110 111
#define INC_111 112
#define INC_112 113
#define INC_113 114
#define INC_114 115
#define INC_115 116
#define INC_116 117
#define INC_117 118
#define INC_118 119
#define INC_119 120
#define INC_120 121
#define INC_121 122
#define INC_122 123
#define INC_123 124
#define INC_124 125
#define INC_125 126
#define INC_126 127
#define INC_127 128

#define MUL_0 0
#define MUL_1 2
#define MUL_2 4
#define MUL_3 6
#define MUL_4 8
#define MUL_5 10
#define MUL_6 12
#define MUL_7 14
#define MUL_8 16
#define MUL_9 18
#define MUL_10 20
#define MUL_11 22
#define MUL_12 24
#define MUL_13 26
#define MUL_14 28
#define MUL_15 30
#define MUL_16 32
#define MUL_17 34
#define MUL_18 36
#define MUL_19 38
#define MUL_20 40
#define MUL_21 42
#define MUL_22 44
#define MUL_23 46
#define MUL_24 48
#define MUL_25 50
#define MUL_26 52
#define MUL_27 54
#define MUL_28 56
#define MUL_29 58
#define MUL_30 60
#define MUL_31 62
#define MUL_32 64
#define MUL_33 66
#define MUL_34 68
#define MUL_35 70
#define MUL_36 72
#define MUL_37 74
#define MUL_38 76
#define MUL_39 78
#define MUL_40 80
#define MUL_41 82
#define MUL_42 84
#define MUL_43 86
#define MUL_44 88
#define MUL_45 90
#define MUL_46 92
#define MUL_47 94
#define MUL_48 96
#define MUL_49 98
#define MUL_50 100
#define MUL_51 102
#define MUL_52 104
#define MUL_53 106
#define MUL_54 108
#define MUL_55 110
#define MUL_56 112
#define MUL_57 114
#define MUL_58 116
#define MUL_59 118
#define MUL_60 120
#define MUL_61 122
#define MUL_62 124
#define MUL_63 126
#define MUL_64 128
#define MUL_65 130
#define MUL_66 132
#define MUL_67 134
#define MUL_68 136
#define MUL_69 138
#define MUL_70 140
#define MUL_71 142
#define MUL_72 144
#define MUL_73 146
#define MUL_74 148
#define MUL_75 150
#define MUL_76 152
#define MUL_77 154
#define MUL_78 156
#define MUL_79 158
#define MUL_80 160
#define MUL_81 162
#define MUL_82 164
#define MUL_83 166
#define MUL_84 168
#define MUL_85 170
#define MUL_86 172
#define MUL_87 174
#define MUL_88 176
#define MUL_89 178
#define MUL_90 180
#define MUL_91 182
#define MUL_92 184
#define MUL_93 186
#define MUL_94 188
#define MUL_95 190
#define MUL_96 192
#define MUL_97 194
#define MUL_98 196
#define MUL_99 198
#define MUL_100 200
#define MUL_101 202
#define MUL_102 204
#define MUL_103 206
#define MUL_104 208
#define MUL_105 210
#define MUL_106 212
#define MUL_107 214
#define MUL_108 216
#define MUL_109 218
#define MUL_110 220
#define MUL_111 222
#define MUL_112 224
#define MUL_113 226
#define MUL_114 228
#define MUL_115 230
#define MUL_116 232
#define MUL_117 234
#define MUL_118 236
#define MUL_119 238
#define MUL_120 240
#define MUL_121 242
#define MUL_122 244
#define MUL_123 246
#define MUL_124 248
#define MUL_125 250
#define MUL_126 252
#define MUL_127 254
#define MUL_128 256

#define EVAL2(...) EVAL1(EVAL1(__VA_ARGS__))
#define EVAL3(...) EVAL2(EVAL1(__VA_ARGS__))
#define EVAL4(...) EVAL3(EVAL1(__VA_ARGS__))
#define EVAL5(...) EVAL4(EVAL1(__VA_ARGS__))
#define EVAL6(...) EVAL5(EVAL1(__VA_ARGS__))
#define EVAL7(...) EVAL6(EVAL1(__VA_ARGS__))
#define EVAL8(...) EVAL7(EVAL1(__VA_ARGS__))
#define EVAL9(...) EVAL8(EVAL1(__VA_ARGS__))
#define EVAL10(...) EVAL9(EVAL1(__VA_ARGS__))
#define EVAL11(...) EVAL10(EVAL1(__VA_ARGS__))
#define EVAL12(...) EVAL11(EVAL1(__VA_ARGS__))
#define EVAL13(...) EVAL12(EVAL1(__VA_ARGS__))
#define EVAL14(...) EVAL13(EVAL1(__VA_ARGS__))
#define EVAL15(...) EVAL14(EVAL1(__VA_ARGS__))
#define EVAL16(...) EVAL15(EVAL1(__VA_ARGS__))
#define EVAL17(...) EVAL16(EVAL1(__VA_ARGS__))
#define EVAL18(...) EVAL17(EVAL1(__VA_ARGS__))
#define EVAL19(...) EVAL18(EVAL1(__VA_ARGS__))
#define EVAL20(...) EVAL19(EVAL1(__VA_ARGS__))
#define EVAL21(...) EVAL20(EVAL1(__VA_ARGS__))
#define EVAL22(...) EVAL21(EVAL1(__VA_ARGS__))
#define EVAL23(...) EVAL22(EVAL1(__VA_ARGS__))
#define EVAL24(...) EVAL23(EVAL1(__VA_ARGS__))
#define EVAL25(...) EVAL24(EVAL1(__VA_ARGS__))
#define EVAL26(...) EVAL25(EVAL1(__VA_ARGS__))
#define EVAL27(...) EVAL26(EVAL1(__VA_ARGS__))
#define EVAL28(...) EVAL27(EVAL1(__VA_ARGS__))
#define EVAL29(...) EVAL28(EVAL1(__VA_ARGS__))
#define EVAL30(...) EVAL29(EVAL1(__VA_ARGS__))
#define EVAL31(...) EVAL30(EVAL1(__VA_ARGS__))
#define EVAL32(...) EVAL31(EVAL1(__VA_ARGS__))
#define EVAL33(...) EVAL32(EVAL1(__VA_ARGS__))
#define EVAL34(...) EVAL33(EVAL1(__VA_ARGS__))
#define EVAL35(...) EVAL34(EVAL1(__VA_ARGS__))
#define EVAL36(...) EVAL35(EVAL1(__VA_ARGS__))
#define EVAL37(...) EVAL36(EVAL1(__VA_ARGS__))
#define EVAL38(...) EVAL37(EVAL1(__VA_ARGS__))
#define EVAL39(...) EVAL38(EVAL1(__VA_ARGS__))
#define EVAL40(...) EVAL39(EVAL1(__VA_ARGS__))
#define EVAL41(...) EVAL40(EVAL1(__VA_ARGS__))
#define EVAL42(...) EVAL41(EVAL1(__VA_ARGS__))
#define EVAL43(...) EVAL42(EVAL1(__VA_ARGS__))
#define EVAL44(...) EVAL43(EVAL1(__VA_ARGS__))
#define EVAL45(...) EVAL44(EVAL1(__VA_ARGS__))
#define EVAL46(...) EVAL45(EVAL1(__VA_ARGS__))
#define EVAL47(...) EVAL46(EVAL1(__VA_ARGS__))
#define EVAL48(...) EVAL47(EVAL1(__VA_ARGS__))
#define EVAL49(...) EVAL48(EVAL1(__VA_ARGS__))
#define EVAL50(...) EVAL49(EVAL1(__VA_ARGS__))
#define EVAL51(...) EVAL50(EVAL1(__VA_ARGS__))
#define EVAL52(...) EVAL51(EVAL1(__VA_ARGS__))
#define EVAL53(...) EVAL52(EVAL1(__VA_ARGS__))
#define EVAL54(...) EVAL53(EVAL1(__VA_ARGS__))
#define EVAL55(...) EVAL54(EVAL1(__VA_ARGS__))
#define EVAL56(...) EVAL55(EVAL1(__VA_ARGS__))
#define EVAL57(...) EVAL56(EVAL1(__VA_ARGS__))
#define EVAL58(...) EVAL57(EVAL1(__VA_ARGS__))
#define EVAL59(...) EVAL58(EVAL1(__VA_ARGS__))
#define EVAL60(...) EVAL59(EVAL1(__VA_ARGS__))
#define EVAL61(...) EVAL60(EVAL1(__VA_ARGS__))
#define EVAL62(...) EVAL61(EVAL1(__VA_ARGS__))
#define EVAL63(...) EVAL62(EVAL1(__VA_ARGS__))
#define EVAL64(...) EVAL63(EVAL1(__VA_ARGS__))
#define EVAL65(...) EVAL64(EVAL1(__VA_ARGS__))
#define EVAL66(...) EVAL65(EVAL1(__VA_ARGS__))
#define EVAL67(...) EVAL66(EVAL1(__VA_ARGS__))
#define EVAL68(...) EVAL67(EVAL1(__VA_ARGS__))
#define EVAL69(...) EVAL68(EVAL1(__VA_ARGS__))
#define EVAL70(...) EVAL69(EVAL1(__VA_ARGS__))
#define EVAL71(...) EVAL70(EVAL1(__VA_ARGS__))
#define EVAL72(...) EVAL71(EVAL1(__VA_ARGS__))
#define EVAL73(...) EVAL72(EVAL1(__VA_ARGS__))
#define EVAL74(...) EVAL73(EVAL1(__VA_ARGS__))
#define EVAL75(...) EVAL74(EVAL1(__VA_ARGS__))
#define EVAL76(...) EVAL75(EVAL1(__VA_ARGS__))
#define EVAL77(...) EVAL76(EVAL1(__VA_ARGS__))
#define EVAL78(...) EVAL77(EVAL1(__VA_ARGS__))
#define EVAL79(...) EVAL78(EVAL1(__VA_ARGS__))
#define EVAL80(...) EVAL79(EVAL1(__VA_ARGS__))
#define EVAL81(...) EVAL80(EVAL1(__VA_ARGS__))
#define EVAL82(...) EVAL81(EVAL1(__VA_ARGS__))
#define EVAL83(...) EVAL82(EVAL1(__VA_ARGS__))
#define EVAL84(...) EVAL83(EVAL1(__VA_ARGS__))
#define EVAL85(...) EVAL84(EVAL1(__VA_ARGS__))
#define EVAL86(...) EVAL85(EVAL1(__VA_ARGS__))
#define EVAL87(...) EVAL86(EVAL1(__VA_ARGS__))
#define EVAL88(...) EVAL87(EVAL1(__VA_ARGS__))
#define EVAL89(...) EVAL88(EVAL1(__VA_ARGS__))
#define EVAL90(...) EVAL89(EVAL1(__VA_ARGS__))
#define EVAL91(...) EVAL90(EVAL1(__VA_ARGS__))
#define EVAL92(...) EVAL91(EVAL1(__VA_ARGS__))
#define EVAL93(...) EVAL92(EVAL1(__VA_ARGS__))
#define EVAL94(...) EVAL93(EVAL1(__VA_ARGS__))
#define EVAL95(...) EVAL94(EVAL1(__VA_ARGS__))
#define EVAL96(...) EVAL95(EVAL1(__VA_ARGS__))
#define EVAL97(...) EVAL96(EVAL1(__VA_ARGS__))
#define EVAL98(...) EVAL97(EVAL1(__VA_ARGS__))
#define EVAL99(...) EVAL98(EVAL1(__VA_ARGS__))
#define EVAL100(...) EVAL99(EVAL1(__VA_ARGS__))
#define EVAL101(...) EVAL100(EVAL1(__VA_ARGS__))
#define EVAL102(...) EVAL101(EVAL1(__VA_ARGS__))
#define EVAL103(...) EVAL102(EVAL1(__VA_ARGS__))
#define EVAL104(...) EVAL103(EVAL1(__VA_ARGS__))
#define EVAL105(...) EVAL104(EVAL1(__VA_ARGS__))
#define EVAL106(...) EVAL105(EVAL1(__VA_ARGS__))
#define EVAL107(...) EVAL106(EVAL1(__VA_ARGS__))
#define EVAL108(...) EVAL107(EVAL1(__VA_ARGS__))
#define EVAL109(...) EVAL108(EVAL1(__VA_ARGS__))
#define EVAL110(...) EVAL109(EVAL1(__VA_ARGS__))
#define EVAL111(...) EVAL110(EVAL1(__VA_ARGS__))
#define EVAL112(...) EVAL111(EVAL1(__VA_ARGS__))
#define EVAL113(...) EVAL112(EVAL1(__VA_ARGS__))
#define EVAL114(...) EVAL113(EVAL1(__VA_ARGS__))
#define EVAL115(...) EVAL114(EVAL1(__VA_ARGS__))
#define EVAL116(...) EVAL115(EVAL1(__VA_ARGS__))
#define EVAL117(...) EVAL116(EVAL1(__VA_ARGS__))
#define EVAL118(...) EVAL117(EVAL1(__VA_ARGS__))
#define EVAL119(...) EVAL118(EVAL1(__VA_ARGS__))
#define EVAL120(...) EVAL119(EVAL1(__VA_ARGS__))
#define EVAL121(...) EVAL120(EVAL1(__VA_ARGS__))
#define EVAL122(...) EVAL121(EVAL1(__VA_ARGS__))
#define EVAL123(...) EVAL122(EVAL1(__VA_ARGS__))
#define EVAL124(...) EVAL123(EVAL1(__VA_ARGS__))
#define EVAL125(...) EVAL124(EVAL1(__VA_ARGS__))
#define EVAL126(...) EVAL125(EVAL1(__VA_ARGS__))
#define EVAL127(...) EVAL126(EVAL1(__VA_ARGS__))
#define EVAL128(...) EVAL127(EVAL1(__VA_ARGS__))

#endif