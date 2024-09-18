/*
 * Generated with obj2c.c from rat_lofi.obj on 2024-09-18
 */

#ifndef RAT_LOFI_H_INCLUDED
#define RAT_LOFI_H_INCLUDED

#include "model.h"

extern model_t rat_lofi_model;

#ifdef RAT_LOFI_IMPL

static const vec_t verts[199] = {
	VEC(95102, 17006, 258285),
	VEC(80531, 15850, 266815),
	VEC(55396, 19642, 235297),
	VEC(60738, 12409, 260451),
	VEC(-47087, 100298, 234289),
	VEC(94527, 29325, 170163),
	VEC(70617, 39898, 165642),
	VEC(169060, 296591, -10722),
	VEC(126025, 128121, -2047),
	VEC(85511, 86594, 29229),
	VEC(117893, 194001, 186545),
	VEC(38113, 83753, 51300),
	VEC(55021, 103200, 244360),
	VEC(58566, 33463, 114281),
	VEC(131713, 40678, 85704),
	VEC(89529, 4067, 122636),
	VEC(91222, 82525, 165205),
	VEC(95283, 129125, 214799),
	VEC(151312, 205091, 61140),
	VEC(157233, 85314, 78300),
	VEC(149733, 159746, 137104),
	VEC(60163, 68625, 122284),
	VEC(68839, 27884, 194717),
	VEC(70673, 29624, 246104),
	VEC(69686, 5565, 292436),
	VEC(80323, -753, 203935),
	VEC(122431, 16417, -165056),
	VEC(137201, 6010, -179763),
	VEC(127159, 8131, -234004),
	VEC(92431, 21385, -188395),
	VEC(101796, 17883, -155783),
	VEC(90217, 62599, -268004),
	VEC(187003, 207199, -363177),
	VEC(146097, 142304, -162064),
	VEC(98528, 12013, -292381),
	VEC(108023, 37194, -250987),
	VEC(134217, 41199, -311556),
	VEC(176884, 93308, -299063),
	VEC(205091, 127075, -224371),
	VEC(183341, 329262, -246214),
	VEC(211474, 230726, -270418),
	VEC(119644, 9046, -133774),
	VEC(118381, 29970, -165285),
	VEC(142979, 17718, -176700),
	VEC(134864, 65136, -253780),
	VEC(108584, 102286, -178349),
	VEC(141018, 12810, -141051),
	VEC(192363, 268554, -190451),
	VEC(26832, 57903, -80512),
	VEC(49044, 98198, -254032),
	VEC(86142, 87175, -329035),
	VEC(66268, 329778, 283883),
	VEC(127833, 339773, 224796),
	VEC(104138, 333184, 207085),
	VEC(101829, 399261, 252955),
	VEC(121898, 382126, 217627),
	VEC(62807, 376775, 260390),
	VEC(96051, 391982, 220374),
	VEC(79820, 303385, 263760),
	VEC(50999, 329438, 246063),
	VEC(90014, 326253, 227646),
	VEC(77696, 371957, 241812),
	VEC(44387, 342555, 263658),
	VEC(96509, 411802, -55997),
	VEC(78094, 435611, -203642),
	VEC(99419, 313106, 120544),
	VEC(-18188, 444242, -127827),
	VEC(45185, 408245, -333853),
	VEC(89396, 27677, -183955),
	VEC(94872, 167827, -418851),
	VEC(94954, 126916, -384259),
	VEC(-75588, 119316, -404525),
	VEC(42250, 107554, -405291),
	VEC(53, 351931, -401211),
	VEC(98617, 218262, 361291),
	VEC(12658, 160817, -523230),
	VEC(48293, 115375, -503264),
	VEC(8748, 14364, -1126690),
	VEC(17027, 51919, -688960),
	VEC(-8241, 9221, -1084256),
	VEC(14727, 102241, -639667),
	VEC(60518, 262670, 386714),
	VEC(7158, 239759, 439621),
	VEC(-5095, 108376, 412192),
	VEC(96495, 269969, 238763),
	VEC(43482, 214765, 399365),
	VEC(38894, 249819, 398324),
	VEC(66774, 221929, 370172),
	VEC(59391, 257315, 373103),
	VEC(71027, 223886, 399026),
	VEC(34170, 116977, 418166),
	VEC(58226, 190572, 431113),
	VEC(64962, 142011, 407367),
	VEC(50074, 233539, 400092),
	VEC(11743, 154084, 537354),
	VEC(14481, 117351, 491822),
	VEC(57659, 137657, 478913),
	VEC(113286, 347404, -373487),
	VEC(48905, 211105, -457882),
	VEC(-78985, 18523, 265381),
	VEC(-51780, 23148, 234556),
	VEC(-74548, 33475, 178077),
	VEC(-83498, 1670, 184743),
	VEC(-169596, 279485, 4404),
	VEC(-123611, 122854, -2710),
	VEC(-50501, 81442, 31725),
	VEC(-103475, 135572, 210413),
	VEC(-93025, 36748, 168377),
	VEC(-109945, 237717, 179771),
	VEC(-88267, 331689, 126398),
	VEC(-91223, 3658, 123107),
	VEC(-152367, 73302, 69040),
	VEC(-151462, 212046, 68819),
	VEC(-147240, 133832, 144421),
	VEC(-56958, 66276, 101862),
	VEC(-86416, 79757, 37792),
	VEC(-84409, 79365, 163141),
	VEC(69, 98681, 147758),
	VEC(-55888, 8206, 275760),
	VEC(-57635, 11697, 238999),
	VEC(-90530, 21302, 252886),
	VEC(-97322, 12720, 258624),
	VEC(-67071, 13380, 278226),
	VEC(-143999, 9041, -139151),
	VEC(-125276, 27424, -168149),
	VEC(-122119, 13680, -166529),
	VEC(-119123, 8866, -133410),
	VEC(-101641, 23152, -160207),
	VEC(-188525, 112178, -218667),
	VEC(-37946, 64538, -25625),
	VEC(-153467, 148227, -166129),
	VEC(-66044, 98771, -217703),
	VEC(-128314, 34184, -312242),
	VEC(-174392, 80612, -286546),
	VEC(-89926, 85793, -331654),
	VEC(-214063, 165177, -237970),
	VEC(-92870, 60200, -270785),
	VEC(-121066, 113931, -169429),
	VEC(-100889, 34522, -252780),
	VEC(-127116, 22038, -210795),
	VEC(-147944, 14970, -174570),
	VEC(-136901, 3351, -189912),
	VEC(-88225, 23339, -182543),
	VEC(-134645, 64386, -255061),
	VEC(-180789, 224495, -121987),
	VEC(-50323, 91954, -328986),
	VEC(-102235, 13825, -298814),
	VEC(-126348, 36094, -261888),
	VEC(-106997, 330066, 205213),
	VEC(-72603, 257974, 372589),
	VEC(-75426, 303317, 265859),
	VEC(-128095, 362706, 212986),
	VEC(-75979, 375424, 270279),
	VEC(-108686, 401836, 242055),
	VEC(-89510, 389221, 223017),
	VEC(-96826, 283096, 237808),
	VEC(-68446, 324017, 286852),
	VEC(-117060, 325852, 231424),
	VEC(-81757, 375146, 234666),
	VEC(-50468, 329644, 249026),
	VEC(-105912, 390531, -19518),
	VEC(-192512, 315575, -227604),
	VEC(-115534, 414221, -175245),
	VEC(-33665, 425540, -310712),
	VEC(15011, 370390, 104484),
	VEC(-108122, 353594, -372695),
	VEC(-104113, 187326, -418859),
	VEC(-23601, 208773, -477342),
	VEC(-190807, 228641, -352374),
	VEC(-178648, 146335, -338385),
	VEC(-23109, 133335, -545246),
	VEC(-44552, 105192, -499873),
	VEC(-14178, 51916, -628160),
	VEC(-7421, 57730, -838107),
	VEC(-101482, 221606, 350848),
	VEC(-56815, 258775, 401251),
	VEC(-51556, 339665, 250504),
	VEC(-37935, 219835, 404857),
	VEC(-66594, 215526, 372291),
	VEC(-64221, 245125, 368694),
	VEC(-67338, 252431, 399501),
	VEC(-46080, 257824, 387964),
	VEC(-61752, 135888, 408219),
	VEC(-72529, 226932, 379833),
	VEC(-2978, 141010, 526058),
	VEC(-28370, 159960, 526366),
	VEC(-54144, 126089, 465145),
	VEC(-13520, 114619, 484820),
	VEC(-46531, 232478, 412611),
	VEC(-62197, 180085, 430381),
	VEC(54, 3587, -1456685),
	VEC(1372, 122105, 490397),
	VEC(-308, 125660, 474572),
	VEC(97, 119417, 490284),
	VEC(-239, 121441, 490915),
	VEC(21711, 111857, 472937),
	VEC(-250, 122424, 491270),
	VEC(-104, 122368, 489210),
	VEC(-576, 139434, 490684),
};

static const vec_t norms[384] = {
	VEC(9061, -64556, 6726),
	VEC(16264, -60996, -17601),
	VEC(13619, 56178, 30879),
	VEC(-43874, 43513, 21830),
	VEC(49454, -22161, 36853),
	VEC(59885, 1560, 26576),
	VEC(55300, 23216, 26417),
	VEC(-43680, -48228, -7805),
	VEC(54137, -2829, 36825),
	VEC(11057, -45396, -45953),
	VEC(43351, -37539, 31724),
	VEC(45607, -31825, -34670),
	VEC(65330, 3744, 3593),
	VEC(9282, -63807, 11719),
	VEC(61014, -409, -23916),
	VEC(3339, -62936, 17966),
	VEC(-22951, -59308, 15831),
	VEC(-30285, -58042, -2961),
	VEC(-44564, -47858, -4296),
	VEC(-44051, 43439, 21619),
	VEC(-35549, 55053, -595),
	VEC(-61220, -22535, 6256),
	VEC(31409, 10346, 56581),
	VEC(-6865, -64982, -5004),
	VEC(24598, 42493, -43407),
	VEC(-21974, -61594, 4263),
	VEC(-19698, 24665, 57433),
	VEC(46887, -42484, 17077),
	VEC(-56027, -21782, 26103),
	VEC(-64665, -10639, 33),
	VEC(15328, -52852, -35588),
	VEC(58196, 21742, -20866),
	VEC(63071, 16186, 7417),
	VEC(20668, -2019, -62158),
	VEC(-32792, -49093, 28450),
	VEC(-22908, 54168, 28914),
	VEC(985, 64909, 8991),
	VEC(22186, 59532, -16084),
	VEC(58841, -28846, -735),
	VEC(-27913, -57868, 12918),
	VEC(-17779, 52218, 35386),
	VEC(62020, 18703, 9934),
	VEC(61710, -21573, 4627),
	VEC(42475, -48911, -9923),
	VEC(19251, -61518, -11821),
	VEC(3819, -64262, 12276),
	VEC(29454, 51306, 28197),
	VEC(-1356, 14267, -63949),
	VEC(-44553, 4683, -47832),
	VEC(-33489, 55949, -6560),
	VEC(-33814, 23089, 51170),
	VEC(50435, -35602, -21992),
	VEC(914, 11060, 64590),
	VEC(51747, -34548, -20580),
	VEC(32695, -8589, 56144),
	VEC(21652, 49315, 37339),
	VEC(41782, 47826, -16180),
	VEC(54027, 26497, -25960),
	VEC(9244, 62984, -15573),
	VEC(59232, -18038, -21474),
	VEC(36339, 15256, -52360),
	VEC(60592, -24371, 5440),
	VEC(63192, -10152, -14094),
	VEC(63943, 2356, 14167),
	VEC(36088, -29235, -46236),
	VEC(9947, 48552, -42879),
	VEC(20048, -61539, 10287),
	VEC(65355, 4582, -1628),
	VEC(10402, -64484, 5336),
	VEC(64211, 10555, -7779),
	VEC(53636, 37566, -2639),
	VEC(61257, -21176, 9697),
	VEC(60311, 23916, 9250),
	VEC(63715, 14499, 5015),
	VEC(12988, -63893, 6623),
	VEC(62349, -16959, 10952),
	VEC(1652, -65480, 2124),
	VEC(10409, 54886, 34266),
	VEC(557, 65189, -6712),
	VEC(-1006, 54902, 35773),
	VEC(5744, 62448, 19031),
	VEC(157, 1966, 65506),
	VEC(63188, 14033, -10264),
	VEC(57565, -6950, 30543),
	VEC(49806, 29331, 30887),
	VEC(37760, -53443, 3593),
	VEC(37624, 41213, 34363),
	VEC(31036, -38858, 42682),
	VEC(22091, -52657, 32158),
	VEC(64924, 5598, 6967),
	VEC(41580, -50642, 1163),
	VEC(36651, 36202, 40511),
	VEC(38896, -34010, -40314),
	VEC(36482, -9585, -53592),
	VEC(14426, 28591, -57178),
	VEC(10249, -60169, 23863),
	VEC(3381, 64481, 11215),
	VEC(52653, -34205, -18776),
	VEC(-60766, 15282, 19203),
	VEC(-39421, -40879, 32707),
	VEC(55861, -33306, -8075),
	VEC(-58998, 23112, 16730),
	VEC(63058, -16149, 7603),
	VEC(-55583, -25127, 23958),
	VEC(-8516, -48252, -43520),
	VEC(-54363, 7315, 35861),
	VEC(-65405, 433, 4100),
	VEC(23005, -59826, 13655),
	VEC(675, -64064, -13789),
	VEC(5252, -63363, 15887),
	VEC(8671, 62680, 17057),
	VEC(-23231, -61207, -2962),
	VEC(58499, 19728, 21992),
	VEC(-12921, -55352, 32619),
	VEC(-30107, 57899, -6012),
	VEC(-55557, 34431, 4778),
	VEC(-2303, 63158, 17341),
	VEC(46518, -45207, 9341),
	VEC(10953, -59491, -25212),
	VEC(-49509, 4148, 42738),
	VEC(23115, 30204, 53370),
	VEC(-45450, -47078, 3562),
	VEC(-22084, -20518, 58191),
	VEC(-35082, -52624, 17168),
	VEC(-60401, -18043, -17916),
	VEC(64424, -11875, -1877),
	VEC(-64350, 9750, -7671),
	VEC(-48186, -29389, -33304),
	VEC(-7504, -17955, -62579),
	VEC(-23055, -51442, 33421),
	VEC(13779, -54942, 32960),
	VEC(10952, -59750, -24593),
	VEC(75, 57810, 30869),
	VEC(63022, 15637, -8873),
	VEC(22680, -60069, 13121),
	VEC(-64323, -8375, 9340),
	VEC(-5178, -63487, -15405),
	VEC(-52139, 34234, 20110),
	VEC(-55865, 14589, 31001),
	VEC(-48254, 36231, 25569),
	VEC(-3570, 64345, 11911),
	VEC(-61599, -1838, 22295),
	VEC(4198, 17707, -62958),
	VEC(41080, 3194, -50962),
	VEC(38831, 52622, 4245),
	VEC(53618, 18451, 32858),
	VEC(-53394, -28540, -25087),
	VEC(-44752, -47264, 7630),
	VEC(-16893, -32146, 54554),
	VEC(-27703, -307, 59391),
	VEC(-14782, 43748, 46504),
	VEC(-53197, -28918, -25072),
	VEC(-17014, 63090, -5010),
	VEC(-23724, 60161, 10618),
	VEC(-53396, 36935, 8918),
	VEC(-63506, 6150, -14964),
	VEC(-11398, 61016, 21026),
	VEC(-46067, 44045, -15252),
	VEC(-52934, 31358, -22571),
	VEC(-23759, 60919, -4391),
	VEC(-2271, -64952, 8422),
	VEC(-59954, -25523, 6991),
	VEC(-61388, -12354, -19331),
	VEC(-57718, -27316, -14740),
	VEC(-24549, 54106, -27655),
	VEC(-6167, -62917, 17269),
	VEC(-58411, 27864, -10322),
	VEC(-2708, 56761, 32647),
	VEC(-60424, 24807, 5325),
	VEC(-4583, 64960, -7355),
	VEC(-41396, -30688, 40491),
	VEC(-23803, 58828, -16358),
	VEC(-46986, 26638, 37116),
	VEC(-19196, -62581, 3153),
	VEC(-32326, -43905, 36362),
	VEC(-4652, 49049, 43215),
	VEC(12927, -63866, 6989),
	VEC(-64896, -4604, 7881),
	VEC(-55333, 24932, 24728),
	VEC(-43085, -14393, -47237),
	VEC(-64876, 9131, -1582),
	VEC(9884, -50185, 40972),
	VEC(-58357, 27166, 12303),
	VEC(-25925, -45961, 38862),
	VEC(26431, -20125, 56492),
	VEC(-64390, -7816, -9360),
	VEC(-28281, 54687, 22460),
	VEC(26899, -59260, 7716),
	VEC(-31782, 57186, -3811),
	VEC(12165, 64391, -890),
	VEC(16463, 56153, 29509),
	VEC(9465, -62356, 17803),
	VEC(4985, 64721, 9015),
	VEC(31242, 57529, -3062),
	VEC(-53688, -29160, -23708),
	VEC(-56844, 31222, 9426),
	VEC(56846, 27468, 17578),
	VEC(63549, 14881, 5918),
	VEC(43973, -48547, 2100),
};

static const face_t faces[384] = {
	(face_t) { .v0 = 1, .v1 = 3, .v2 = 0, .n = 0 },
	(face_t) { .v0 = 3, .v1 = 1, .v2 = 24, .n = 1 },
	(face_t) { .v0 = 23, .v1 = 1, .v2 = 0, .n = 2 },
	(face_t) { .v0 = 23, .v1 = 2, .v2 = 3, .n = 3 },
	(face_t) { .v0 = 19, .v1 = 16, .v2 = 14, .n = 4 },
	(face_t) { .v0 = 14, .v1 = 5, .v2 = 25, .n = 5 },
	(face_t) { .v0 = 7, .v1 = 65, .v2 = 10, .n = 6 },
	(face_t) { .v0 = 15, .v1 = 25, .v2 = 13, .n = 7 },
	(face_t) { .v0 = 17, .v1 = 20, .v2 = 10, .n = 8 },
	(face_t) { .v0 = 14, .v1 = 9, .v2 = 8, .n = 9 },
	(face_t) { .v0 = 16, .v1 = 19, .v2 = 17, .n = 10 },
	(face_t) { .v0 = 19, .v1 = 14, .v2 = 8, .n = 11 },
	(face_t) { .v0 = 19, .v1 = 18, .v2 = 20, .n = 12 },
	(face_t) { .v0 = 9, .v1 = 11, .v2 = 48, .n = 13 },
	(face_t) { .v0 = 19, .v1 = 8, .v2 = 18, .n = 14 },
	(face_t) { .v0 = 21, .v1 = 16, .v2 = 12, .n = 15 },
	(face_t) { .v0 = 21, .v1 = 12, .v2 = 117, .n = 16 },
	(face_t) { .v0 = 21, .v1 = 117, .v2 = 11, .n = 17 },
	(face_t) { .v0 = 3, .v1 = 2, .v2 = 25, .n = 18 },
	(face_t) { .v0 = 3, .v1 = 24, .v2 = 23, .n = 19 },
	(face_t) { .v0 = 23, .v1 = 22, .v2 = 2, .n = 20 },
	(face_t) { .v0 = 25, .v1 = 22, .v2 = 13, .n = 21 },
	(face_t) { .v0 = 42, .v1 = 26, .v2 = 43, .n = 22 },
	(face_t) { .v0 = 30, .v1 = 29, .v2 = 26, .n = 23 },
	(face_t) { .v0 = 29, .v1 = 68, .v2 = 42, .n = 24 },
	(face_t) { .v0 = 34, .v1 = 27, .v2 = 29, .n = 25 },
	(face_t) { .v0 = 44, .v1 = 31, .v2 = 35, .n = 26 },
	(face_t) { .v0 = 37, .v1 = 44, .v2 = 36, .n = 27 },
	(face_t) { .v0 = 34, .v1 = 35, .v2 = 31, .n = 28 },
	(face_t) { .v0 = 34, .v1 = 31, .v2 = 50, .n = 29 },
	(face_t) { .v0 = 70, .v1 = 37, .v2 = 50, .n = 30 },
	(face_t) { .v0 = 40, .v1 = 32, .v2 = 39, .n = 31 },
	(face_t) { .v0 = 47, .v1 = 40, .v2 = 39, .n = 32 },
	(face_t) { .v0 = 36, .v1 = 50, .v2 = 37, .n = 33 },
	(face_t) { .v0 = 49, .v1 = 31, .v2 = 45, .n = 34 },
	(face_t) { .v0 = 30, .v1 = 42, .v2 = 68, .n = 35 },
	(face_t) { .v0 = 26, .v1 = 46, .v2 = 43, .n = 36 },
	(face_t) { .v0 = 42, .v1 = 43, .v2 = 28, .n = 37 },
	(face_t) { .v0 = 43, .v1 = 46, .v2 = 27, .n = 38 },
	(face_t) { .v0 = 27, .v1 = 46, .v2 = 26, .n = 39 },
	(face_t) { .v0 = 42, .v1 = 30, .v2 = 41, .n = 40 },
	(face_t) { .v0 = 26, .v1 = 42, .v2 = 41, .n = 41 },
	(face_t) { .v0 = 18, .v1 = 33, .v2 = 47, .n = 42 },
	(face_t) { .v0 = 48, .v1 = 8, .v2 = 9, .n = 43 },
	(face_t) { .v0 = 49, .v1 = 45, .v2 = 48, .n = 44 },
	(face_t) { .v0 = 129, .v1 = 48, .v2 = 11, .n = 45 },
	(face_t) { .v0 = 63, .v1 = 164, .v2 = 65, .n = 46 },
	(face_t) { .v0 = 55, .v1 = 53, .v2 = 57, .n = 47 },
	(face_t) { .v0 = 57, .v1 = 53, .v2 = 62, .n = 48 },
	(face_t) { .v0 = 54, .v1 = 57, .v2 = 56, .n = 49 },
	(face_t) { .v0 = 56, .v1 = 62, .v2 = 51, .n = 50 },
	(face_t) { .v0 = 51, .v1 = 61, .v2 = 54, .n = 51 },
	(face_t) { .v0 = 52, .v1 = 55, .v2 = 60, .n = 52 },
	(face_t) { .v0 = 61, .v1 = 51, .v2 = 59, .n = 53 },
	(face_t) { .v0 = 61, .v1 = 60, .v2 = 55, .n = 54 },
	(face_t) { .v0 = 60, .v1 = 59, .v2 = 58, .n = 55 },
	(face_t) { .v0 = 97, .v1 = 64, .v2 = 39, .n = 56 },
	(face_t) { .v0 = 97, .v1 = 39, .v2 = 32, .n = 57 },
	(face_t) { .v0 = 64, .v1 = 67, .v2 = 163, .n = 58 },
	(face_t) { .v0 = 70, .v1 = 76, .v2 = 69, .n = 59 },
	(face_t) { .v0 = 32, .v1 = 98, .v2 = 97, .n = 60 },
	(face_t) { .v0 = 18, .v1 = 8, .v2 = 33, .n = 61 },
	(face_t) { .v0 = 38, .v1 = 32, .v2 = 40, .n = 62 },
	(face_t) { .v0 = 40, .v1 = 47, .v2 = 38, .n = 63 },
	(face_t) { .v0 = 37, .v1 = 70, .v2 = 32, .n = 64 },
	(face_t) { .v0 = 98, .v1 = 75, .v2 = 167, .n = 65 },
	(face_t) { .v0 = 172, .v1 = 78, .v2 = 72, .n = 66 },
	(face_t) { .v0 = 78, .v1 = 77, .v2 = 80, .n = 67 },
	(face_t) { .v0 = 78, .v1 = 172, .v2 = 77, .n = 68 },
	(face_t) { .v0 = 72, .v1 = 78, .v2 = 80, .n = 69 },
	(face_t) { .v0 = 77, .v1 = 190, .v2 = 173, .n = 70 },
	(face_t) { .v0 = 92, .v1 = 10, .v2 = 74, .n = 71 },
	(face_t) { .v0 = 51, .v1 = 74, .v2 = 58, .n = 72 },
	(face_t) { .v0 = 10, .v1 = 84, .v2 = 74, .n = 73 },
	(face_t) { .v0 = 12, .v1 = 90, .v2 = 83, .n = 74 },
	(face_t) { .v0 = 92, .v1 = 17, .v2 = 10, .n = 75 },
	(face_t) { .v0 = 4, .v1 = 117, .v2 = 12, .n = 76 },
	(face_t) { .v0 = 82, .v1 = 81, .v2 = 62, .n = 77 },
	(face_t) { .v0 = 66, .v1 = 64, .v2 = 163, .n = 78 },
	(face_t) { .v0 = 51, .v1 = 62, .v2 = 81, .n = 79 },
	(face_t) { .v0 = 164, .v1 = 63, .v2 = 66, .n = 80 },
	(face_t) { .v0 = 86, .v1 = 85, .v2 = 89, .n = 81 },
	(face_t) { .v0 = 87, .v1 = 88, .v2 = 89, .n = 82 },
	(face_t) { .v0 = 74, .v1 = 91, .v2 = 92, .n = 83 },
	(face_t) { .v0 = 93, .v1 = 94, .v2 = 96, .n = 84 },
	(face_t) { .v0 = 96, .v1 = 195, .v2 = 90, .n = 85 },
	(face_t) { .v0 = 82, .v1 = 94, .v2 = 93, .n = 86 },
	(face_t) { .v0 = 96, .v1 = 184, .v2 = 95, .n = 87 },
	(face_t) { .v0 = 184, .v1 = 96, .v2 = 94, .n = 88 },
	(face_t) { .v0 = 96, .v1 = 92, .v2 = 91, .n = 89 },
	(face_t) { .v0 = 92, .v1 = 96, .v2 = 90, .n = 90 },
	(face_t) { .v0 = 91, .v1 = 93, .v2 = 96, .n = 91 },
	(face_t) { .v0 = 70, .v1 = 69, .v2 = 32, .n = 92 },
	(face_t) { .v0 = 32, .v1 = 69, .v2 = 98, .n = 93 },
	(face_t) { .v0 = 167, .v1 = 97, .v2 = 98, .n = 94 },
	(face_t) { .v0 = 121, .v1 = 119, .v2 = 99, .n = 95 },
	(face_t) { .v0 = 120, .v1 = 99, .v2 = 101, .n = 96 },
	(face_t) { .v0 = 102, .v1 = 100, .v2 = 119, .n = 97 },
	(face_t) { .v0 = 113, .v1 = 108, .v2 = 112, .n = 98 },
	(face_t) { .v0 = 116, .v1 = 4, .v2 = 106, .n = 99 },
	(face_t) { .v0 = 110, .v1 = 114, .v2 = 102, .n = 100 },
	(face_t) { .v0 = 112, .v1 = 108, .v2 = 109, .n = 101 },
	(face_t) { .v0 = 114, .v1 = 101, .v2 = 102, .n = 102 },
	(face_t) { .v0 = 111, .v1 = 107, .v2 = 113, .n = 103 },
	(face_t) { .v0 = 115, .v1 = 110, .v2 = 104, .n = 104 },
	(face_t) { .v0 = 108, .v1 = 113, .v2 = 106, .n = 105 },
	(face_t) { .v0 = 113, .v1 = 112, .v2 = 111, .n = 106 },
	(face_t) { .v0 = 114, .v1 = 117, .v2 = 4, .n = 107 },
	(face_t) { .v0 = 115, .v1 = 105, .v2 = 114, .n = 108 },
	(face_t) { .v0 = 4, .v1 = 116, .v2 = 114, .n = 109 },
	(face_t) { .v0 = 100, .v1 = 99, .v2 = 122, .n = 110 },
	(face_t) { .v0 = 99, .v1 = 119, .v2 = 122, .n = 111 },
	(face_t) { .v0 = 101, .v1 = 114, .v2 = 116, .n = 112 },
	(face_t) { .v0 = 140, .v1 = 141, .v2 = 125, .n = 113 },
	(face_t) { .v0 = 124, .v1 = 139, .v2 = 140, .n = 114 },
	(face_t) { .v0 = 139, .v1 = 132, .v2 = 141, .n = 115 },
	(face_t) { .v0 = 139, .v1 = 138, .v2 = 147, .n = 116 },
	(face_t) { .v0 = 131, .v1 = 136, .v2 = 145, .n = 117 },
	(face_t) { .v0 = 134, .v1 = 71, .v2 = 145, .n = 118 },
	(face_t) { .v0 = 161, .v1 = 135, .v2 = 130, .n = 119 },
	(face_t) { .v0 = 138, .v1 = 136, .v2 = 143, .n = 120 },
	(face_t) { .v0 = 132, .v1 = 147, .v2 = 133, .n = 121 },
	(face_t) { .v0 = 147, .v1 = 138, .v2 = 143, .n = 122 },
	(face_t) { .v0 = 133, .v1 = 143, .v2 = 128, .n = 123 },
	(face_t) { .v0 = 135, .v1 = 169, .v2 = 133, .n = 124 },
	(face_t) { .v0 = 134, .v1 = 136, .v2 = 146, .n = 125 },
	(face_t) { .v0 = 168, .v1 = 135, .v2 = 161, .n = 126 },
	(face_t) { .v0 = 133, .v1 = 169, .v2 = 132, .n = 127 },
	(face_t) { .v0 = 134, .v1 = 132, .v2 = 169, .n = 128 },
	(face_t) { .v0 = 128, .v1 = 143, .v2 = 137, .n = 129 },
	(face_t) { .v0 = 136, .v1 = 131, .v2 = 137, .n = 130 },
	(face_t) { .v0 = 134, .v1 = 145, .v2 = 136, .n = 131 },
	(face_t) { .v0 = 124, .v1 = 126, .v2 = 127, .n = 132 },
	(face_t) { .v0 = 146, .v1 = 138, .v2 = 142, .n = 133 },
	(face_t) { .v0 = 141, .v1 = 142, .v2 = 127, .n = 134 },
	(face_t) { .v0 = 112, .v1 = 103, .v2 = 144, .n = 135 },
	(face_t) { .v0 = 131, .v1 = 49, .v2 = 48, .n = 136 },
	(face_t) { .v0 = 103, .v1 = 109, .v2 = 160, .n = 137 },
	(face_t) { .v0 = 109, .v1 = 103, .v2 = 112, .n = 138 },
	(face_t) { .v0 = 175, .v1 = 156, .v2 = 149, .n = 139 },
	(face_t) { .v0 = 176, .v1 = 62, .v2 = 164, .n = 140 },
	(face_t) { .v0 = 152, .v1 = 150, .v2 = 156, .n = 141 },
	(face_t) { .v0 = 151, .v1 = 154, .v2 = 148, .n = 142 },
	(face_t) { .v0 = 148, .v1 = 154, .v2 = 176, .n = 143 },
	(face_t) { .v0 = 154, .v1 = 153, .v2 = 152, .n = 144 },
	(face_t) { .v0 = 176, .v1 = 152, .v2 = 156, .n = 145 },
	(face_t) { .v0 = 151, .v1 = 148, .v2 = 157, .n = 146 },
	(face_t) { .v0 = 158, .v1 = 152, .v2 = 153, .n = 147 },
	(face_t) { .v0 = 151, .v1 = 158, .v2 = 153, .n = 148 },
	(face_t) { .v0 = 151, .v1 = 159, .v2 = 158, .n = 149 },
	(face_t) { .v0 = 150, .v1 = 159, .v2 = 157, .n = 150 },
	(face_t) { .v0 = 155, .v1 = 157, .v2 = 148, .n = 151 },
	(face_t) { .v0 = 66, .v1 = 163, .v2 = 162, .n = 152 },
	(face_t) { .v0 = 162, .v1 = 160, .v2 = 66, .n = 153 },
	(face_t) { .v0 = 161, .v1 = 160, .v2 = 162, .n = 154 },
	(face_t) { .v0 = 148, .v1 = 109, .v2 = 108, .n = 155 },
	(face_t) { .v0 = 66, .v1 = 160, .v2 = 164, .n = 156 },
	(face_t) { .v0 = 161, .v1 = 162, .v2 = 165, .n = 157 },
	(face_t) { .v0 = 161, .v1 = 165, .v2 = 168, .n = 158 },
	(face_t) { .v0 = 148, .v1 = 164, .v2 = 109, .n = 159 },
	(face_t) { .v0 = 49, .v1 = 145, .v2 = 50, .n = 160 },
	(face_t) { .v0 = 104, .v1 = 144, .v2 = 130, .n = 161 },
	(face_t) { .v0 = 135, .v1 = 168, .v2 = 169, .n = 162 },
	(face_t) { .v0 = 171, .v1 = 71, .v2 = 166, .n = 163 },
	(face_t) { .v0 = 170, .v1 = 75, .v2 = 80, .n = 164 },
	(face_t) { .v0 = 172, .v1 = 72, .v2 = 71, .n = 165 },
	(face_t) { .v0 = 170, .v1 = 173, .v2 = 171, .n = 166 },
	(face_t) { .v0 = 82, .v1 = 156, .v2 = 175, .n = 167 },
	(face_t) { .v0 = 150, .v1 = 108, .v2 = 174, .n = 168 },
	(face_t) { .v0 = 174, .v1 = 188, .v2 = 183, .n = 169 },
	(face_t) { .v0 = 177, .v1 = 180, .v2 = 178, .n = 170 },
	(face_t) { .v0 = 180, .v1 = 181, .v2 = 179, .n = 171 },
	(face_t) { .v0 = 174, .v1 = 189, .v2 = 188, .n = 172 },
	(face_t) { .v0 = 187, .v1 = 186, .v2 = 83, .n = 173 },
	(face_t) { .v0 = 185, .v1 = 187, .v2 = 184, .n = 174 },
	(face_t) { .v0 = 82, .v1 = 185, .v2 = 94, .n = 175 },
	(face_t) { .v0 = 187, .v1 = 83, .v2 = 90, .n = 176 },
	(face_t) { .v0 = 182, .v1 = 186, .v2 = 189, .n = 177 },
	(face_t) { .v0 = 189, .v1 = 185, .v2 = 188, .n = 178 },
	(face_t) { .v0 = 166, .v1 = 169, .v2 = 168, .n = 179 },
	(face_t) { .v0 = 190, .v1 = 79, .v2 = 173, .n = 180 },
	(face_t) { .v0 = 191, .v1 = 187, .v2 = 195, .n = 181 },
	(face_t) { .v0 = 191, .v1 = 192, .v2 = 193, .n = 182 },
	(face_t) { .v0 = 192, .v1 = 195, .v2 = 198, .n = 183 },
	(face_t) { .v0 = 194, .v1 = 191, .v2 = 196, .n = 184 },
	(face_t) { .v0 = 194, .v1 = 197, .v2 = 193, .n = 185 },
	(face_t) { .v0 = 192, .v1 = 187, .v2 = 193, .n = 186 },
	(face_t) { .v0 = 194, .v1 = 187, .v2 = 191, .n = 187 },
	(face_t) { .v0 = 187, .v1 = 196, .v2 = 197, .n = 188 },
	(face_t) { .v0 = 196, .v1 = 191, .v2 = 197, .n = 189 },
	(face_t) { .v0 = 23, .v1 = 24, .v2 = 1, .n = 190 },
	(face_t) { .v0 = 3, .v1 = 25, .v2 = 0, .n = 191 },
	(face_t) { .v0 = 0, .v1 = 5, .v2 = 22, .n = 192 },
	(face_t) { .v0 = 23, .v1 = 0, .v2 = 22, .n = 193 },
	(face_t) { .v0 = 22, .v1 = 25, .v2 = 2, .n = 194 },
	(face_t) { .v0 = 22, .v1 = 6, .v2 = 13, .n = 195 },
	(face_t) { .v0 = 10, .v1 = 20, .v2 = 18, .n = 196 },
	(face_t) { .v0 = 47, .v1 = 39, .v2 = 7, .n = 197 },
	(face_t) { .v0 = 15, .v1 = 14, .v2 = 25, .n = 198 },
	(face_t) { .v0 = 6, .v1 = 16, .v2 = 13, .n = 199 },
	(face_t) { .v0 = 6, .v1 = 5, .v2 = 16, .n = 200 },
	(face_t) { .v0 = 14, .v1 = 16, .v2 = 5, .n = 201 },
	(face_t) { .v0 = 15, .v1 = 13, .v2 = 9, .n = 202 },
	(face_t) { .v0 = 17, .v1 = 19, .v2 = 20, .n = 203 },
	(face_t) { .v0 = 17, .v1 = 12, .v2 = 16, .n = 204 },
	(face_t) { .v0 = 117, .v1 = 105, .v2 = 11, .n = 205 },
	(face_t) { .v0 = 105, .v1 = 129, .v2 = 11, .n = 206 },
	(face_t) { .v0 = 9, .v1 = 14, .v2 = 15, .n = 207 },
	(face_t) { .v0 = 9, .v1 = 13, .v2 = 21, .n = 208 },
	(face_t) { .v0 = 11, .v1 = 9, .v2 = 21, .n = 209 },
	(face_t) { .v0 = 6, .v1 = 22, .v2 = 5, .n = 210 },
	(face_t) { .v0 = 0, .v1 = 25, .v2 = 5, .n = 211 },
	(face_t) { .v0 = 21, .v1 = 13, .v2 = 16, .n = 212 },
	(face_t) { .v0 = 29, .v1 = 27, .v2 = 26, .n = 213 },
	(face_t) { .v0 = 42, .v1 = 35, .v2 = 29, .n = 214 },
	(face_t) { .v0 = 35, .v1 = 42, .v2 = 28, .n = 215 },
	(face_t) { .v0 = 34, .v1 = 28, .v2 = 27, .n = 216 },
	(face_t) { .v0 = 28, .v1 = 36, .v2 = 35, .n = 217 },
	(face_t) { .v0 = 70, .v1 = 50, .v2 = 72, .n = 218 },
	(face_t) { .v0 = 33, .v1 = 38, .v2 = 47, .n = 219 },
	(face_t) { .v0 = 45, .v1 = 44, .v2 = 33, .n = 220 },
	(face_t) { .v0 = 29, .v1 = 35, .v2 = 34, .n = 221 },
	(face_t) { .v0 = 34, .v1 = 36, .v2 = 28, .n = 222 },
	(face_t) { .v0 = 37, .v1 = 38, .v2 = 44, .n = 223 },
	(face_t) { .v0 = 34, .v1 = 50, .v2 = 36, .n = 224 },
	(face_t) { .v0 = 36, .v1 = 44, .v2 = 35, .n = 225 },
	(face_t) { .v0 = 38, .v1 = 37, .v2 = 32, .n = 226 },
	(face_t) { .v0 = 33, .v1 = 44, .v2 = 38, .n = 227 },
	(face_t) { .v0 = 31, .v1 = 49, .v2 = 50, .n = 228 },
	(face_t) { .v0 = 27, .v1 = 28, .v2 = 43, .n = 229 },
	(face_t) { .v0 = 45, .v1 = 31, .v2 = 44, .n = 230 },
	(face_t) { .v0 = 29, .v1 = 30, .v2 = 68, .n = 231 },
	(face_t) { .v0 = 41, .v1 = 30, .v2 = 26, .n = 232 },
	(face_t) { .v0 = 33, .v1 = 8, .v2 = 45, .n = 233 },
	(face_t) { .v0 = 45, .v1 = 8, .v2 = 48, .n = 234 },
	(face_t) { .v0 = 7, .v1 = 18, .v2 = 47, .n = 235 },
	(face_t) { .v0 = 7, .v1 = 63, .v2 = 65, .n = 236 },
	(face_t) { .v0 = 62, .v1 = 53, .v2 = 164, .n = 237 },
	(face_t) { .v0 = 81, .v1 = 74, .v2 = 51, .n = 238 },
	(face_t) { .v0 = 54, .v1 = 55, .v2 = 57, .n = 239 },
	(face_t) { .v0 = 55, .v1 = 52, .v2 = 53, .n = 240 },
	(face_t) { .v0 = 56, .v1 = 51, .v2 = 54, .n = 241 },
	(face_t) { .v0 = 56, .v1 = 57, .v2 = 62, .n = 242 },
	(face_t) { .v0 = 52, .v1 = 58, .v2 = 84, .n = 243 },
	(face_t) { .v0 = 58, .v1 = 59, .v2 = 51, .n = 244 },
	(face_t) { .v0 = 54, .v1 = 61, .v2 = 55, .n = 245 },
	(face_t) { .v0 = 58, .v1 = 52, .v2 = 60, .n = 246 },
	(face_t) { .v0 = 61, .v1 = 59, .v2 = 60, .n = 247 },
	(face_t) { .v0 = 84, .v1 = 53, .v2 = 52, .n = 248 },
	(face_t) { .v0 = 63, .v1 = 7, .v2 = 39, .n = 249 },
	(face_t) { .v0 = 64, .v1 = 63, .v2 = 39, .n = 250 },
	(face_t) { .v0 = 65, .v1 = 164, .v2 = 53, .n = 251 },
	(face_t) { .v0 = 65, .v1 = 53, .v2 = 10, .n = 252 },
	(face_t) { .v0 = 97, .v1 = 67, .v2 = 64, .n = 253 },
	(face_t) { .v0 = 97, .v1 = 73, .v2 = 67, .n = 254 },
	(face_t) { .v0 = 73, .v1 = 97, .v2 = 167, .n = 255 },
	(face_t) { .v0 = 69, .v1 = 76, .v2 = 98, .n = 256 },
	(face_t) { .v0 = 50, .v1 = 71, .v2 = 72, .n = 257 },
	(face_t) { .v0 = 18, .v1 = 7, .v2 = 10, .n = 258 },
	(face_t) { .v0 = 70, .v1 = 72, .v2 = 76, .n = 259 },
	(face_t) { .v0 = 76, .v1 = 80, .v2 = 75, .n = 260 },
	(face_t) { .v0 = 76, .v1 = 72, .v2 = 80, .n = 261 },
	(face_t) { .v0 = 98, .v1 = 76, .v2 = 75, .n = 262 },
	(face_t) { .v0 = 80, .v1 = 77, .v2 = 173, .n = 263 },
	(face_t) { .v0 = 77, .v1 = 172, .v2 = 79, .n = 264 },
	(face_t) { .v0 = 10, .v1 = 53, .v2 = 84, .n = 265 },
	(face_t) { .v0 = 12, .v1 = 83, .v2 = 4, .n = 266 },
	(face_t) { .v0 = 58, .v1 = 74, .v2 = 84, .n = 267 },
	(face_t) { .v0 = 92, .v1 = 90, .v2 = 17, .n = 268 },
	(face_t) { .v0 = 12, .v1 = 17, .v2 = 90, .n = 269 },
	(face_t) { .v0 = 93, .v1 = 91, .v2 = 74, .n = 270 },
	(face_t) { .v0 = 81, .v1 = 93, .v2 = 74, .n = 271 },
	(face_t) { .v0 = 66, .v1 = 63, .v2 = 64, .n = 272 },
	(face_t) { .v0 = 88, .v1 = 86, .v2 = 89, .n = 273 },
	(face_t) { .v0 = 85, .v1 = 87, .v2 = 89, .n = 274 },
	(face_t) { .v0 = 81, .v1 = 82, .v2 = 93, .n = 275 },
	(face_t) { .v0 = 95, .v1 = 195, .v2 = 96, .n = 276 },
	(face_t) { .v0 = 90, .v1 = 195, .v2 = 187, .n = 277 },
	(face_t) { .v0 = 79, .v1 = 190, .v2 = 77, .n = 278 },
	(face_t) { .v0 = 119, .v1 = 100, .v2 = 118, .n = 279 },
	(face_t) { .v0 = 118, .v1 = 122, .v2 = 119, .n = 280 },
	(face_t) { .v0 = 107, .v1 = 120, .v2 = 101, .n = 281 },
	(face_t) { .v0 = 102, .v1 = 101, .v2 = 100, .n = 282 },
	(face_t) { .v0 = 102, .v1 = 111, .v2 = 110, .n = 283 },
	(face_t) { .v0 = 113, .v1 = 107, .v2 = 116, .n = 284 },
	(face_t) { .v0 = 111, .v1 = 102, .v2 = 107, .n = 285 },
	(face_t) { .v0 = 116, .v1 = 106, .v2 = 113, .n = 286 },
	(face_t) { .v0 = 104, .v1 = 110, .v2 = 111, .n = 287 },
	(face_t) { .v0 = 110, .v1 = 115, .v2 = 114, .n = 288 },
	(face_t) { .v0 = 112, .v1 = 104, .v2 = 111, .n = 289 },
	(face_t) { .v0 = 115, .v1 = 104, .v2 = 105, .n = 290 },
	(face_t) { .v0 = 155, .v1 = 148, .v2 = 108, .n = 291 },
	(face_t) { .v0 = 117, .v1 = 114, .v2 = 105, .n = 292 },
	(face_t) { .v0 = 104, .v1 = 129, .v2 = 105, .n = 293 },
	(face_t) { .v0 = 118, .v1 = 100, .v2 = 122, .n = 294 },
	(face_t) { .v0 = 100, .v1 = 101, .v2 = 99, .n = 295 },
	(face_t) { .v0 = 121, .v1 = 102, .v2 = 119, .n = 296 },
	(face_t) { .v0 = 102, .v1 = 121, .v2 = 107, .n = 297 },
	(face_t) { .v0 = 120, .v1 = 107, .v2 = 121, .n = 298 },
	(face_t) { .v0 = 101, .v1 = 116, .v2 = 107, .n = 299 },
	(face_t) { .v0 = 120, .v1 = 121, .v2 = 99, .n = 300 },
	(face_t) { .v0 = 123, .v1 = 140, .v2 = 125, .n = 301 },
	(face_t) { .v0 = 125, .v1 = 141, .v2 = 127, .n = 302 },
	(face_t) { .v0 = 140, .v1 = 139, .v2 = 141, .n = 303 },
	(face_t) { .v0 = 142, .v1 = 138, .v2 = 124, .n = 304 },
	(face_t) { .v0 = 139, .v1 = 124, .v2 = 138, .n = 305 },
	(face_t) { .v0 = 139, .v1 = 147, .v2 = 132, .n = 306 },
	(face_t) { .v0 = 166, .v1 = 71, .v2 = 169, .n = 307 },
	(face_t) { .v0 = 134, .v1 = 146, .v2 = 132, .n = 308 },
	(face_t) { .v0 = 138, .v1 = 146, .v2 = 136, .n = 309 },
	(face_t) { .v0 = 133, .v1 = 147, .v2 = 143, .n = 310 },
	(face_t) { .v0 = 130, .v1 = 135, .v2 = 128, .n = 311 },
	(face_t) { .v0 = 133, .v1 = 128, .v2 = 135, .n = 312 },
	(face_t) { .v0 = 71, .v1 = 134, .v2 = 169, .n = 313 },
	(face_t) { .v0 = 128, .v1 = 137, .v2 = 130, .n = 314 },
	(face_t) { .v0 = 136, .v1 = 137, .v2 = 143, .n = 315 },
	(face_t) { .v0 = 127, .v1 = 142, .v2 = 124, .n = 316 },
	(face_t) { .v0 = 125, .v1 = 127, .v2 = 126, .n = 317 },
	(face_t) { .v0 = 125, .v1 = 124, .v2 = 123, .n = 318 },
	(face_t) { .v0 = 123, .v1 = 124, .v2 = 140, .n = 319 },
	(face_t) { .v0 = 142, .v1 = 141, .v2 = 146, .n = 320 },
	(face_t) { .v0 = 141, .v1 = 132, .v2 = 146, .n = 321 },
	(face_t) { .v0 = 126, .v1 = 124, .v2 = 125, .n = 322 },
	(face_t) { .v0 = 144, .v1 = 161, .v2 = 130, .n = 323 },
	(face_t) { .v0 = 137, .v1 = 104, .v2 = 130, .n = 324 },
	(face_t) { .v0 = 137, .v1 = 129, .v2 = 104, .n = 325 },
	(face_t) { .v0 = 103, .v1 = 161, .v2 = 144, .n = 326 },
	(face_t) { .v0 = 48, .v1 = 129, .v2 = 131, .n = 327 },
	(face_t) { .v0 = 49, .v1 = 131, .v2 = 145, .n = 328 },
	(face_t) { .v0 = 137, .v1 = 131, .v2 = 129, .n = 329 },
	(face_t) { .v0 = 164, .v1 = 148, .v2 = 176, .n = 330 },
	(face_t) { .v0 = 176, .v1 = 156, .v2 = 62, .n = 331 },
	(face_t) { .v0 = 154, .v1 = 151, .v2 = 153, .n = 332 },
	(face_t) { .v0 = 176, .v1 = 154, .v2 = 152, .n = 333 },
	(face_t) { .v0 = 150, .v1 = 157, .v2 = 155, .n = 334 },
	(face_t) { .v0 = 152, .v1 = 159, .v2 = 150, .n = 335 },
	(face_t) { .v0 = 158, .v1 = 159, .v2 = 152, .n = 336 },
	(face_t) { .v0 = 159, .v1 = 151, .v2 = 157, .n = 337 },
	(face_t) { .v0 = 149, .v1 = 156, .v2 = 174, .n = 338 },
	(face_t) { .v0 = 161, .v1 = 103, .v2 = 160, .n = 339 },
	(face_t) { .v0 = 165, .v1 = 162, .v2 = 163, .n = 340 },
	(face_t) { .v0 = 163, .v1 = 67, .v2 = 73, .n = 341 },
	(face_t) { .v0 = 163, .v1 = 73, .v2 = 165, .n = 342 },
	(face_t) { .v0 = 50, .v1 = 145, .v2 = 71, .n = 343 },
	(face_t) { .v0 = 106, .v1 = 174, .v2 = 108, .n = 344 },
	(face_t) { .v0 = 104, .v1 = 112, .v2 = 144, .n = 345 },
	(face_t) { .v0 = 171, .v1 = 167, .v2 = 170, .n = 346 },
	(face_t) { .v0 = 75, .v1 = 170, .v2 = 167, .n = 347 },
	(face_t) { .v0 = 171, .v1 = 172, .v2 = 71, .n = 348 },
	(face_t) { .v0 = 173, .v1 = 79, .v2 = 172, .n = 349 },
	(face_t) { .v0 = 173, .v1 = 172, .v2 = 171, .n = 350 },
	(face_t) { .v0 = 80, .v1 = 173, .v2 = 170, .n = 351 },
	(face_t) { .v0 = 182, .v1 = 4, .v2 = 83, .n = 352 },
	(face_t) { .v0 = 82, .v1 = 175, .v2 = 188, .n = 353 },
	(face_t) { .v0 = 156, .v1 = 150, .v2 = 174, .n = 354 },
	(face_t) { .v0 = 150, .v1 = 155, .v2 = 108, .n = 355 },
	(face_t) { .v0 = 182, .v1 = 106, .v2 = 4, .n = 356 },
	(face_t) { .v0 = 189, .v1 = 174, .v2 = 182, .n = 357 },
	(face_t) { .v0 = 174, .v1 = 106, .v2 = 182, .n = 358 },
	(face_t) { .v0 = 183, .v1 = 149, .v2 = 174, .n = 359 },
	(face_t) { .v0 = 82, .v1 = 62, .v2 = 156, .n = 360 },
	(face_t) { .v0 = 177, .v1 = 181, .v2 = 180, .n = 361 },
	(face_t) { .v0 = 179, .v1 = 178, .v2 = 180, .n = 362 },
	(face_t) { .v0 = 175, .v1 = 149, .v2 = 188, .n = 363 },
	(face_t) { .v0 = 188, .v1 = 149, .v2 = 183, .n = 364 },
	(face_t) { .v0 = 94, .v1 = 185, .v2 = 184, .n = 365 },
	(face_t) { .v0 = 82, .v1 = 188, .v2 = 185, .n = 366 },
	(face_t) { .v0 = 187, .v1 = 185, .v2 = 186, .n = 367 },
	(face_t) { .v0 = 95, .v1 = 184, .v2 = 187, .n = 368 },
	(face_t) { .v0 = 83, .v1 = 186, .v2 = 182, .n = 369 },
	(face_t) { .v0 = 189, .v1 = 186, .v2 = 185, .n = 370 },
	(face_t) { .v0 = 165, .v1 = 166, .v2 = 168, .n = 371 },
	(face_t) { .v0 = 167, .v1 = 166, .v2 = 165, .n = 372 },
	(face_t) { .v0 = 167, .v1 = 171, .v2 = 166, .n = 373 },
	(face_t) { .v0 = 165, .v1 = 73, .v2 = 167, .n = 374 },
	(face_t) { .v0 = 160, .v1 = 109, .v2 = 164, .n = 375 },
	(face_t) { .v0 = 191, .v1 = 195, .v2 = 192, .n = 376 },
	(face_t) { .v0 = 198, .v1 = 195, .v2 = 95, .n = 377 },
	(face_t) { .v0 = 193, .v1 = 197, .v2 = 191, .n = 378 },
	(face_t) { .v0 = 194, .v1 = 196, .v2 = 197, .n = 379 },
	(face_t) { .v0 = 187, .v1 = 198, .v2 = 95, .n = 380 },
	(face_t) { .v0 = 192, .v1 = 198, .v2 = 187, .n = 381 },
	(face_t) { .v0 = 187, .v1 = 197, .v2 = 193, .n = 382 },
	(face_t) { .v0 = 194, .v1 = 196, .v2 = 187, .n = 383 },
};

model_t rat_lofi_model = (model_t) {
	.verts = verts,
	.nverts = 199,
	.norms = norms,
	.nnorms = 384,
	.faces = faces,
	.nfaces = 384,
};

#endif
#endif
