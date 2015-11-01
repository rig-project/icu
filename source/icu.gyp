{
  "includes": [
    "common.gypi"
  ],

  'target_defaults': {
    'cflags_cc': [
      # Enable RTTI.
      '-frtti',
      '-fno-exceptions',
      '--std=c++11',
    ],
    'defines': [
      'U_DISABLE_RENAMING=1',
      'U_HAVE_ATOMIC=1',
      'U_HAVE_ELF_H',

       # TODO: make conditional...
      'HAVE_DIRENT_H=1',
      'HAVE_DLFCN_H=1',
      'HAVE_DLOPEN=1',
      'HAVE_ELF_H=1',
      'HAVE_GETTIMEOFDAY=1',
      'HAVE_INTTYPES_H=1',
      'HAVE_MEMORY_H=1',
      'HAVE_STDINT_H=1',
      'HAVE_STDLIB_H=1',
      'HAVE_STRINGS_H=1',
      'HAVE_STRING_H=1',
      'HAVE_SYS_STAT_H=1',
      'HAVE_SYS_TYPES_H=1',
      'HAVE_UNISTD_H=1',

      'PACKAGE="International Components for Unicode"',
      'PACKAGE_BUGREPORT="http://icu-project.org/bugs"',
      'PACKAGE_NAME="ICU"',
      'PACKAGE_STRING="ICU 53.1.0"',
      'PACKAGE_TARNAME="International Components for Unicode"',
      'PACKAGE_URL="http://icu-project.org"',
      'PACKAGE_VERSION="53.1.0"',
      'STDC_HEADERS=1',
    ],
    'conditions': [
      ['OS=="ios"', {
	'xcode_settings': {
	  'WARNING_CFLAGS': [
	    # ICU uses its own deprecated functions.
	    '-Wno-deprecated-declarations',
	    # ICU prefers `a && b || c` over `(a && b) || c`.
	    '-Wno-logical-op-parentheses',
	    # ICU has some `unsigned < 0` checks.
	    '-Wno-tautological-compare',
	    # uresdata.c has switch(RES_GET_TYPE(x)) code. The
	    # RES_GET_TYPE macro returns an UResType enum, but some switch
	    # statement contains case values that aren't part of that
	    # enum (e.g. URES_TABLE32 which is in UResInternalType). This
	    # is on purpose.
	    '-Wno-switch',
	  ],
	},
      }],
      ['OS=="android"', {
        'cflags': [
          '-D__ANDROID__',
        ],
      }],
    ],
    'include_dirs': [
      'common',
      'i18n',
    ],
  },

  'actions': [
    {
      'action_name': 'rig-proto',
      'inputs': [
	'rig/rig.proto'
      ],
      'outputs': [
        'rig/rig.pb-c.h',
        'rig/rig.pb-c.c'
      ],
      'actions': [ 'protoc-c', '--c_out=rig', 'rig.proto' ]
    }
  ],

  'targets': [
    {
      'target_name': 'icuuc',
      'type': '<(library)',
      'dependencies': [
       ],
      'include_dirs': [
        '.',
      ],
      'all_dependent_settings': {
        'include_dirs': [
          'common',
	],
        'defines': [
          'U_DISABLE_RENAMING=1'
        ]
      },
      'defines': [
	'U_COMMON_IMPLEMENTATION',
      ],
      'sources': [
	'common/errorcode.cpp',
	'common/putil.cpp',
	'common/umath.c',
	'common/utypes.c',
	'common/uinvchar.c',
	'common/umutex.cpp',
	'common/ucln_cmn.c',
	'common/uinit.cpp',
	'common/uobject.cpp',
	'common/cmemory.c',
	'common/charstr.cpp',
	'common/udata.cpp',
	'common/ucmndata.c',
	'common/udatamem.c',
	'common/umapfile.c',
	'common/udataswp.c',
	'common/ucol_swp.cpp',
	'common/utrace.c',
	'common/uhash.c',
	'common/uhash_us.cpp',
	'common/uenum.c',
	'common/ustrenum.cpp',
	'common/uvector.cpp',
	'common/ustack.cpp',
	'common/uvectr32.cpp',
	'common/uvectr64.cpp',
	'common/ucnv.c',
	'common/ucnv_bld.cpp',
	'common/ucnv_cnv.c',
	'common/ucnv_io.cpp',
	'common/ucnv_cb.c',
	'common/ucnv_err.c',
	'common/ucnvlat1.c',
	'common/ucnv_u7.c',
	'common/ucnv_u8.c',
	'common/ucnv_u16.c',
	'common/ucnv_u32.c',
	'common/ucnvscsu.c',
	'common/ucnvbocu.cpp',
	'common/ucnv_ext.cpp',
	'common/ucnvmbcs.c',
	'common/ucnv2022.cpp',
	'common/ucnvhz.c',
	'common/ucnv_lmb.c',
	'common/ucnvisci.c',
	'common/ucnvdisp.c',
	'common/ucnv_set.c',
	'common/ucnv_ct.c',
	'common/uresbund.cpp',
	'common/ures_cnv.c',
	'common/uresdata.c',
	'common/resbund.cpp',
	'common/resbund_cnv.cpp',
	'common/messagepattern.cpp',
	'common/ucat.c',
	'common/locmap.c',
	'common/uloc.cpp',
	'common/locid.cpp',
	'common/locutil.cpp',
	'common/locavailable.cpp',
	'common/locdispnames.cpp',
	'common/loclikely.cpp',
	'common/locresdata.cpp',
	'common/bytestream.cpp',
	'common/stringpiece.cpp',
	'common/stringtriebuilder.cpp',
	'common/bytestriebuilder.cpp',
	'common/bytestrie.cpp',
	'common/bytestrieiterator.cpp',
	'common/ucharstrie.cpp',
	'common/ucharstriebuilder.cpp',
	'common/ucharstrieiterator.cpp',
	'common/dictionarydata.cpp',
	'common/appendable.cpp',
	'common/ustr_cnv.c',
	'common/unistr_cnv.cpp',
	'common/unistr.cpp',
	'common/unistr_case.cpp',
	'common/unistr_props.cpp',
	'common/utf_impl.c',
	'common/ustring.cpp',
	'common/ustrcase.cpp',
	'common/ucasemap.cpp',
	'common/ucasemap_titlecase_brkiter.cpp',
	'common/cstring.c',
	'common/ustrfmt.c',
	'common/ustrtrns.cpp',
	'common/ustr_wcs.cpp',
	'common/utext.cpp',
	'common/unistr_case_locale.cpp',
	'common/ustrcase_locale.cpp',
	'common/unistr_titlecase_brkiter.cpp',
	'common/ustr_titlecase_brkiter.cpp',
	'common/normalizer2impl.cpp',
	'common/normalizer2.cpp',
	'common/filterednormalizer2.cpp',
	'common/normlzr.cpp',
	'common/unorm.cpp',
	'common/unormcmp.cpp',
	'common/chariter.cpp',
	'common/schriter.cpp',
	'common/uchriter.cpp',
	'common/uiter.cpp',
	'common/patternprops.cpp',
	'common/uchar.c',
	'common/uprops.cpp',
	'common/ucase.cpp',
	'common/propname.cpp',
	'common/ubidi_props.c',
	'common/ubidi.c',
	'common/ubidiwrt.c',
	'common/ubidiln.c',
	'common/ushape.cpp',
	'common/uscript.c',
	'common/uscript_props.cpp',
	'common/usc_impl.c',
	'common/unames.cpp',
	'common/utrie.cpp',
	'common/utrie2.cpp',
	'common/utrie2_builder.cpp',
	'common/bmpset.cpp',
	'common/unisetspan.cpp',
	'common/uset_props.cpp',
	'common/uniset_props.cpp',
	'common/uniset_closure.cpp',
	'common/uset.cpp',
	'common/uniset.cpp',
	'common/usetiter.cpp',
	'common/ruleiter.cpp',
	'common/caniter.cpp',
	'common/unifilt.cpp',
	'common/unifunct.cpp',
	'common/uarrsort.c',
	'common/brkiter.cpp',
	'common/ubrk.cpp',
	'common/brkeng.cpp',
	'common/dictbe.cpp',
	'common/rbbi.cpp',
	'common/rbbidata.cpp',
	'common/rbbinode.cpp',
	'common/rbbirb.cpp',
	'common/rbbiscan.cpp',
	'common/rbbisetb.cpp',
	'common/rbbistbl.cpp',
	'common/rbbitblb.cpp',
	'common/serv.cpp',
	'common/servnotf.cpp',
	'common/servls.cpp',
	'common/servlk.cpp',
	'common/servlkf.cpp',
	'common/servrbf.cpp',
	'common/servslkf.cpp',
	'common/uidna.cpp',
	'common/usprep.cpp',
	'common/uts46.cpp',
	'common/punycode.cpp',
	'common/util.cpp',
	'common/util_props.cpp',
	'common/parsepos.cpp',
	'common/locbased.cpp',
	'common/cwchar.c',
	'common/wintz.c',
	'common/dtintrv.cpp',
	'common/ucnvsel.cpp',
	'common/propsvec.c',
	'common/ulist.c',
	'common/uloc_tag.c',
	'common/icudataver.c',
	'common/icuplug.c',
	'common/listformatter.cpp',
	'common/lrucache.cpp',
	'common/sharedobject.cpp',
	'common/simplepatternformatter.cpp',
      ],
      'conditions': [
        ['_type=="static_library"', {
	  'defines': [
	    'U_STATIC_IMPLEMENTATION',
	  ]
	}],
        ['_type=="shared_library"', {
	  'defines': [
	    'PIC',
	  ],
	  # seems wrong to have to add this manually!?
	  'cflags': [
	    '-fPIC',
	  ]
	}],
        ['OS=="ios"', {
          'xcode_settings': {
            'WARNING_CFLAGS': [
              # ICU uses its own deprecated functions.
              '-Wno-deprecated-declarations',
              # ICU prefers `a && b || c` over `(a && b) || c`.
              '-Wno-logical-op-parentheses',
              # ICU has some `unsigned < 0` checks.
              '-Wno-tautological-compare',
              # uresdata.c has switch(RES_GET_TYPE(x)) code. The
              # RES_GET_TYPE macro returns an UResType enum, but some switch
              # statement contains case values that aren't part of that
              # enum (e.g. URES_TABLE32 which is in UResInternalType). This
              # is on purpose.
              '-Wno-switch',
            ],
          },
        }],
        ['OS=="android"', {
          'cflags_cc': [
            # Path relativisation in 'include_dirs' makes this tricky.
            '-I<(DEPTH)/../android-ndk/sources/android/support/include',
          ],
        }],
      ],
    },
    {
      'target_name': 'icui18n',
      'type': '<(library)',
      'dependencies': [
       ],
      'include_dirs': [
        '.',
	'common',
	'i18n',
	'i18n/unicode',
      ],
      'all_dependent_settings': {
        'include_dirs': [
	],
      },
      'defines': [
	'U_I18N_IMPLEMENTATION'
      ],
      'sources': [
	'i18n/dangical.cpp',
	'i18n/sharedpluralrules.h',
	'i18n/tzrule.cpp',
	'i18n/ethpccal.cpp',
	'i18n/decNumber.h',
	'i18n/nfrule.cpp',
	'i18n/regexst.h',
	'i18n/strmatch.h',
	'i18n/uregion.cpp',
	'i18n/ztrans.h',
	'i18n/regeximp.h',
	'i18n/simpletz.cpp',
	'i18n/ucol_imp.h',
	'i18n/utf8collationiterator.h',
	'i18n/uregexc.cpp',
	'i18n/tmutfmt.cpp',
	'i18n/collationfastlatin.h',
	'i18n/wintzimpl.cpp',
	'i18n/buddhcal.cpp',
	'i18n/fmtable_cnv.cpp',
	'i18n/uspoof_conf.cpp',
	'i18n/regeximp.cpp',
	'i18n/ucoleitr.cpp',
	'i18n/collationrootelements.cpp',
	'i18n/ucol_res.cpp',
	'i18n/indiancal.h',
	'i18n/tztrans.cpp',
	'i18n/buddhcal.h',
	'i18n/dangical.h',
	'i18n/transreg.h',
	'i18n/wintzimpl.h',
	'i18n/collationiterator.h',
	'i18n/cpdtrans.h',
	'i18n/cecal.h',
	'i18n/collationfcd.h',
	'i18n/collation.h',
	'i18n/decNumber.c',
	'i18n/rbt_rule.h',
	'i18n/nfrs.h',
	'i18n/brktrans.h',
	'i18n/plurrule_impl.h',
	'i18n/uitercollationiterator.cpp',
	'i18n/nultrans.cpp',
	'i18n/nfrs.cpp',
	'i18n/nortrans.cpp',
	'i18n/ucsdet.cpp',
	'i18n/collationroot.cpp',
	'i18n/cecal.cpp',
	'i18n/collationbasedatabuilder.cpp',
	'i18n/regextxt.cpp',
	'i18n/anytrans.h',
	'i18n/rbt.cpp',
	'i18n/tmutamt.cpp',
	'i18n/quantityformatter.cpp',
	'i18n/numsys.cpp',
	'i18n/zonemeta.cpp',
	'i18n/nfsubs.h',
	'i18n/unesctrn.cpp',
	'i18n/regexcmp.h',
	'i18n/selfmt.cpp',
	'i18n/esctrn.cpp',
	'i18n/collationdatareader.cpp',
	'i18n/uspoof_conf.h',
	'i18n/currunit.cpp',
	'i18n/nortrans.h',
	'i18n/region.cpp',
	'i18n/ztrans.cpp',
	'i18n/tznames_impl.h',
	'i18n/msgfmt_impl.h',
	'i18n/rulebasedcollator.cpp',
	'i18n/coptccal.cpp',
	'i18n/region_impl.h',
	'i18n/ucal.cpp',
	'i18n/decfmtst.cpp',
	'i18n/decNumberLocal.h',
	'i18n/taiwncal.cpp',
	'i18n/nultrans.h',
	'i18n/upluralrules.cpp',
	'i18n/inputext.h',
	'i18n/uni2name.h',
	'i18n/coptccal.h',
	'i18n/fmtableimp.h',
	'i18n/collationcompare.cpp',
	'i18n/unum.cpp',
	'i18n/uni2name.cpp',
	'i18n/umsg_imp.h',
	'i18n/search.cpp',
	'i18n/windtfmt.cpp',
	'i18n/selfmtimpl.h',
	'i18n/collationkeys.h',
	'i18n/gregocal.cpp',
	'i18n/islamcal.cpp',
	'i18n/tridpars.cpp',
	'i18n/zrule.cpp',
	'i18n/smpdtfst.h',
	'i18n/hebrwcal.h',
	'i18n/rbt_rule.cpp',
	'i18n/reldtfmt.cpp',
	'i18n/coleitr.cpp',
	'i18n/zonemeta.h',
	'i18n/tznames_impl.cpp',
	'i18n/collationdatareader.h',
	'i18n/tzgnames.cpp',
	'i18n/astro.h',
	'i18n/collation.cpp',
	'i18n/dtitvinf.cpp',
	'i18n/gregoimp.cpp',
	'i18n/unicode/udisplaycontext.h',
	'i18n/unicode/smpdtfmt.h',
	'i18n/unicode/datefmt.h',
	'i18n/unicode/ucol.h',
	'i18n/unicode/locdspnm.h',
	'i18n/unicode/choicfmt.h',
	'i18n/unicode/rbtz.h',
	'i18n/unicode/dtrule.h',
	'i18n/unicode/fpositer.h',
	'i18n/unicode/dtitvinf.h',
	'i18n/unicode/umsg.h',
	'i18n/unicode/tztrans.h',
	'i18n/unicode/selfmt.h',
	'i18n/unicode/dtptngen.h',
	'i18n/unicode/ucoleitr.h',
	'i18n/unicode/rbnf.h',
	'i18n/unicode/curramt.h',
	'i18n/unicode/ucal.h',
	'i18n/unicode/region.h',
	'i18n/unicode/vtzone.h',
	'i18n/unicode/format.h',
	'i18n/unicode/decimfmt.h',
	'i18n/unicode/simpletz.h',
	'i18n/unicode/usearch.h',
	'i18n/unicode/numfmt.h',
	'i18n/unicode/msgfmt.h',
	'i18n/unicode/timezone.h',
	'i18n/unicode/fieldpos.h',
	'i18n/unicode/gregocal.h',
	'i18n/unicode/tmutamt.h',
	'i18n/unicode/unumsys.h',
	'i18n/unicode/upluralrules.h',
	'i18n/unicode/udat.h',
	'i18n/unicode/translit.h',
	'i18n/unicode/fmtable.h',
	'i18n/unicode/uregion.h',
	'i18n/unicode/ucsdet.h',
	'i18n/unicode/measunit.h',
	'i18n/unicode/unum.h',
	'i18n/unicode/dtfmtsym.h',
	'i18n/unicode/uformattable.h',
	'i18n/unicode/ugender.h',
	'i18n/unicode/utmscale.h',
	'i18n/unicode/uregex.h',
	'i18n/unicode/alphaindex.h',
	'i18n/unicode/search.h',
	'i18n/unicode/tznames.h',
	'i18n/unicode/calendar.h',
	'i18n/unicode/udateintervalformat.h',
	'i18n/unicode/reldatefmt.h',
	'i18n/unicode/dcfmtsym.h',
	'i18n/unicode/uspoof.h',
	'i18n/unicode/currunit.h',
	'i18n/unicode/measure.h',
	'i18n/unicode/unirepl.h',
	'i18n/unicode/ucurr.h',
	'i18n/unicode/uldnames.h',
	'i18n/unicode/udatpg.h',
	'i18n/unicode/utrans.h',
	'i18n/unicode/dtitvfmt.h',
	'i18n/unicode/compactdecimalformat.h',
	'i18n/unicode/coll.h',
	'i18n/unicode/basictz.h',
	'i18n/unicode/sortkey.h',
	'i18n/unicode/tzrule.h',
	'i18n/unicode/gender.h',
	'i18n/unicode/regex.h',
	'i18n/unicode/tzfmt.h',
	'i18n/unicode/tmunit.h',
	'i18n/unicode/filteredbrk.h',
	'i18n/unicode/ulocdata.h',
	'i18n/unicode/tmutfmt.h',
	'i18n/unicode/plurfmt.h',
	'i18n/unicode/tblcoll.h',
	'i18n/unicode/measfmt.h',
	'i18n/unicode/stsearch.h',
	'i18n/unicode/currpinf.h',
	'i18n/unicode/coleitr.h',
	'i18n/unicode/numsys.h',
	'i18n/unicode/plurrule.h',
	'i18n/quant.h',
	'i18n/fphdlimp.cpp',
	'i18n/udat.cpp',
	'i18n/olsontz.h',
	'i18n/nfrlist.h',
	'i18n/winnmfmt.cpp',
	'i18n/sortkey.cpp',
	'i18n/utf16collationiterator.cpp',
	'i18n/currfmt.h',
	'i18n/dcfmtimp.h',
	'i18n/csdetect.cpp',
	'i18n/regextxt.h',
	'i18n/ucln_in.h',
	'i18n/format.cpp',
	'i18n/indiancal.cpp',
	'i18n/csrmbcs.h',
	'i18n/collationtailoring.cpp',
	'i18n/csmatch.cpp',
	'i18n/collationdata.h',
	'i18n/csrutf8.cpp',
	'i18n/tzgnames.h',
	'i18n/toupptrn.cpp',
	'i18n/ucln_in.c',
	'i18n/chnsecal.cpp',
	'i18n/ucurr.cpp',
	'i18n/ulocdata.c',
	'i18n/chnsecal.h',
	'i18n/csrmbcs.cpp',
	'i18n/quant.cpp',
	'i18n/digitlst.cpp',
	'i18n/unesctrn.h',
	'i18n/timezone.cpp',
	'i18n/ucurrimp.h',
	'i18n/rbtz.cpp',
	'i18n/collationsettings.h',
	'i18n/collationcompare.h',
	'i18n/ucol_sit.cpp',
	'i18n/rbt_data.cpp',
	'i18n/rematch.cpp',
	'i18n/csrecog.cpp',
	'i18n/utf16collationiterator.h',
	'i18n/collationfastlatinbuilder.h',
	'i18n/measunit.cpp',
	'i18n/quantityformatter.h',
	'i18n/utrans.cpp',
	'i18n/tmunit.cpp',
	'i18n/udatpg.cpp',
	'i18n/remtrans.cpp',
	'i18n/japancal.h',
	'i18n/filteredbrk.cpp',
	'i18n/numfmt.cpp',
	'i18n/bocsu.h',
	'i18n/unumsys.cpp',
	'i18n/digitlst.h',
	'i18n/regexcmp.cpp',
	'i18n/collationroot.h',
	'i18n/taiwncal.h',
	'i18n/utmscale.c',
	'i18n/tzfmt.cpp',
	'i18n/japancal.cpp',
	'i18n/reldtfmt.h',
	'i18n/calendar.cpp',
	'i18n/curramt.cpp',
	'i18n/anytrans.cpp',
	'i18n/collationkeys.cpp',
	'i18n/toupptrn.h',
	'i18n/casetrn.h',
	'i18n/collationdatawriter.cpp',
	'i18n/funcrepl.cpp',
	'i18n/tolowtrn.cpp',
	'i18n/measfmt.cpp',
	'i18n/udateintervalformat.cpp',
	'i18n/csrucode.h',
	'i18n/scriptset.cpp',
	'i18n/rbt_pars.cpp',
	'i18n/datefmt.cpp',
	'i18n/dtitv_impl.h',
	'i18n/collationrootelements.h',
	'i18n/name2uni.cpp',
	'i18n/dtitvfmt.cpp',
	'i18n/tolowtrn.h',
	'i18n/collationdata.cpp',
	'i18n/collationweights.h',
	'i18n/dtptngen_impl.h',
	'i18n/winnmfmt.h',
	'i18n/casetrn.cpp',
	'i18n/dtrule.cpp',
	'i18n/hebrwcal.cpp',
	'i18n/remtrans.h',
	'i18n/nfsubs.cpp',
	'i18n/rbt_data.h',
	'i18n/identifier_info.h',
	'i18n/uspoof_wsconf.cpp',
	'i18n/basictz.cpp',
	'i18n/csrsbcs.h',
	'i18n/collationsettings.cpp',
	'i18n/cpdtrans.cpp',
	'i18n/csr2022.cpp',
	'i18n/decContext.c',
	'i18n/esctrn.h',
	'i18n/tznames.cpp',
	'i18n/uregex.cpp',
	'i18n/plurfmt.cpp',
	'i18n/collationdatabuilder.cpp',
	'i18n/collationsets.h',
	'i18n/tridpars.h',
	'i18n/sharednumberformat.h',
	'i18n/rbnf.cpp',
	'i18n/nfrule.h',
	'i18n/identifier_info.cpp',
	'i18n/ethpccal.h',
	'i18n/rbt_set.h',
	'i18n/coll.cpp',
	'i18n/translit.cpp',
	'i18n/collationweights.cpp',
	'i18n/collationsets.cpp',
	'i18n/strmatch.cpp',
	'i18n/fpositer.cpp',
	'i18n/uspoof_impl.cpp',
	'i18n/olsontz.cpp',
	'i18n/decfmtst.h',
	'i18n/titletrn.h',
	'i18n/brktrans.cpp',
	'i18n/decimfmt.cpp',
	'i18n/titletrn.cpp',
	'i18n/collationdatabuilder.h',
	'i18n/transreg.cpp',
	'i18n/decContext.h',
	'i18n/currpinf.cpp',
	'i18n/gender.cpp',
	'i18n/csrecog.h',
	'i18n/vzone.cpp',
	'i18n/usrchimp.h',
	'i18n/gregoimp.h',
	'i18n/uspoof_impl.h',
	'i18n/rbt.h',
	'i18n/reldatefmt.cpp',
	'i18n/strrepl.h',
	'i18n/csmatch.h',
	'i18n/utf8collationiterator.cpp',
	'i18n/smpdtfst.cpp',
	'i18n/collationbasedatabuilder.h',
	'i18n/islamcal.h',
	'i18n/funcrepl.h',
	'i18n/collationfastlatin.cpp',
	'i18n/collationruleparser.h',
	'i18n/fmtable.cpp',
	'i18n/currfmt.cpp',
	'i18n/collationiterator.cpp',
	'i18n/astro.cpp',
	'i18n/collationfastlatinbuilder.cpp',
	'i18n/dcfmtsym.cpp',
	'i18n/msgfmt.cpp',
	'i18n/rbt_pars.h',
	'i18n/repattrn.cpp',
	'i18n/umsg.cpp',
	'i18n/dtfmtsym.cpp',
	'i18n/collationruleparser.cpp',
	'i18n/vzone.h',
	'i18n/stsearch.cpp',
	'i18n/measure.cpp',
	'i18n/strrepl.cpp',
	'i18n/decimalformatpattern.cpp',
	'i18n/uitercollationiterator.h',
	'i18n/persncal.h',
	'i18n/collationbuilder.cpp',
	'i18n/csrutf8.h',
	'i18n/uspoof_wsconf.h',
	'i18n/csr2022.h',
	'i18n/rbt_set.cpp',
	'i18n/uspoof.cpp',
	'i18n/name2uni.h',
	'i18n/regexst.cpp',
	'i18n/persncal.cpp',
	'i18n/locdspnm.cpp',
	'i18n/fphdlimp.h',
	'i18n/csrucode.cpp',
	'i18n/collationfcd.cpp',
	'i18n/compactdecimalformat.cpp',
	'i18n/ucol.cpp',
	'i18n/dtptngen.cpp',
	'i18n/smpdtfmt.cpp',
	'i18n/collationdatawriter.h',
	'i18n/collationtailoring.h',
	'i18n/collationbuilder.h',
	'i18n/usearch.cpp',
	'i18n/zrule.h',
	'i18n/csdetect.h',
	'i18n/inputext.cpp',
	'i18n/choicfmt.cpp',
	'i18n/vtzone.cpp',
	'i18n/uspoof_build.cpp',
	'i18n/regexcst.h',
	'i18n/plurrule.cpp',
	'i18n/csrsbcs.cpp',
	'i18n/alphaindex.cpp',
	'i18n/bocsu.cpp',
	'i18n/numsys_impl.h',
	'i18n/decimalformatpattern.h',
	'i18n/windtfmt.h',
	'i18n/scriptset.h',
      ],

      'conditions': [

        ['_type=="static_library"', {
	  'defines': [
	    'U_STATIC_IMPLEMENTATION',
	  ]
	}],
        ['_type=="shared_library"', {
	  'defines': [
	    'PIC',
	  ],
	  # seems wrong to have to add this manually!?
	  'cflags': [
	    '-fPIC',
	  ]
	}],
      ]
    },
    {
      'target_name': 'icudata',
      'type': '<(library)',
      'dependencies': [
       ],
      'include_dirs': [
        '.',
	'common',
      ],
      'all_dependent_settings': {
        'include_dirs': [
	],
      },
      'defines': [
      ],
      'sources': [
	'stubdata/stubdata.c'
      ],
      'conditions': [

        ['_type=="static_library"', {
	  'defines': [
	    'U_STATIC_IMPLEMENTATION',
	  ]
	}],
        ['_type=="shared_library"', {
	  'defines': [
	    'PIC',
	  ],
	  # seems wrong to have to add this manually!?
	  'cflags': [
	    '-fPIC',
	  ]
	}],
      ]
    },
    {
      'target_name': 'icuio',
      'type': '<(library)',
      'dependencies': [
       ],
      'include_dirs': [
        '.',
	'common',
      ],
      'all_dependent_settings': {
        'include_dirs': [
	],
      },
      'defines': [
	'U_IO_IMPLEMENTATION'
      ],
      'sources': [
	'io/locbund.h',
	'io/locbund.cpp',
	'io/sprintf.c',
	'io/sscanf.c',
	'io/ucln_io.c',
	'io/ucln_io.h',
	'io/ufile.c',
	'io/ufile.h',
	'io/ufmt_cmn.c',
	'io/ufmt_cmn.h',
	'io/uprintf.c',
	'io/uprintf.h',
	'io/uprntf_p.c',
	'io/uscanf.c',
	'io/uscanf.h',
	'io/uscanf_p.c',
	'io/ustdio.c',
	'io/ustream.cpp',
      ],
      'conditions': [

        ['_type=="static_library"', {
	  'defines': [
	    'U_STATIC_IMPLEMENTATION',
	  ]
	}],
        ['_type=="shared_library"', {
	  'defines': [
	    'PIC',
	  ],
	  # seems wrong to have to add this manually!?
	  'cflags': [
	    '-fPIC',
	  ]
	}],
      ]
    },
    {
      'target_name': 'ctestfw',
      'type': 'static_library',
      'dependencies': [
       ],
      'include_dirs': [
        '.',
	'common',
	'i18n',
	'tools/toolutil',
	'tools/ctestfw',
      ],
      'defines': [
	'T_CTESTFW_IMPLEMENTATION'
      ],
      'sources': [
	'tools/ctestfw/unicode/ctest.h',
	'tools/ctestfw/ctest.c',
	'tools/ctestfw/unicode/datamap.h',
	'tools/ctestfw/datamap.cpp',
	'tools/ctestfw/unicode/testdata.h',
	'tools/ctestfw/testdata.cpp',
	'tools/ctestfw/unicode/testlog.h',
	'tools/ctestfw/unicode/testtype.h',
	'tools/ctestfw/unicode/tstdtmod.h',
	'tools/ctestfw/tstdtmod.cpp',
	'tools/ctestfw/unicode/uperf.h',
	'tools/ctestfw/uperf.cpp',
	'tools/ctestfw/unicode/utimer.h',
	'tools/ctestfw/ucln_ct.c',
      ],
    },
    {
      'target_name': 'tool_utils',
      'type': 'static_library',
      'dependencies': [
       ],
      'include_dirs': [
        '.',
	'common',
	'i18n',
	'tools/toolutil',
      ],
      'toolsets': [ 'host' ],
      'direct_dependent_settings': {
        'include_dirs': [
	  'tools/toolutil',
	],
      },
      'defines': [
	'U_TOOLUTIL_IMPLEMENTATION'
      ],
      'sources': [
	'tools/toolutil/collationinfo.cpp',
	'tools/toolutil/collationinfo.h',
	'tools/toolutil/dbgutil.cpp',
	'tools/toolutil/dbgutil.h',
	'tools/toolutil/denseranges.cpp',
	'tools/toolutil/denseranges.h',
	'tools/toolutil/filestrm.c',
	'tools/toolutil/filestrm.h',
	'tools/toolutil/filetools.cpp',
	'tools/toolutil/filetools.h',
	'tools/toolutil/flagparser.c',
	'tools/toolutil/flagparser.h',
	'tools/toolutil/package.cpp',
	'tools/toolutil/package.h',
	'tools/toolutil/pkg_genc.c',
	'tools/toolutil/pkg_genc.h',
	'tools/toolutil/pkg_gencmn.c',
	'tools/toolutil/pkg_gencmn.h',
	'tools/toolutil/pkg_icu.cpp',
	'tools/toolutil/pkg_icu.h',
	'tools/toolutil/pkg_imp.h',
	'tools/toolutil/pkgitems.cpp',
	'tools/toolutil/ppucd.cpp',
	'tools/toolutil/ppucd.h',
	'tools/toolutil/swapimpl.cpp',
	'tools/toolutil/swapimpl.h',
	'tools/toolutil/toolutil.cpp',
	'tools/toolutil/toolutil.h',
	'tools/toolutil/toolutil.vcxproj',
	'tools/toolutil/ucbuf.c',
	'tools/toolutil/ucbuf.h',
	'tools/toolutil/ucln_tu.c',
	'tools/toolutil/ucm.c',
	'tools/toolutil/ucm.h',
	'tools/toolutil/ucmstate.c',
	'tools/toolutil/udbgutil.cpp',
	'tools/toolutil/udbgutil.h',
	'tools/toolutil/unewdata.c',
	'tools/toolutil/unewdata.h',
	'tools/toolutil/uoptions.c',
	'tools/toolutil/uoptions.h',
	'tools/toolutil/uparse.c',
	'tools/toolutil/uparse.h',
	'tools/toolutil/writesrc.c',
	'tools/toolutil/writesrc.h',
	'tools/toolutil/xmlparser.cpp',
	'tools/toolutil/xmlparser.h',
      ],
    },
    {
      'target_name': 'makeconv',
      'type': 'executable',
      'toolsets': [ 'host' ],
      'dependencies': [
	'tool_utils',
	'icuio',
	'icui18n',
	'icuuc',
	'icudata'
       ],
      'sources': [
	'tools/makeconv/gencnvex.c',
	'tools/makeconv/genmbcs.cpp',
	'tools/makeconv/genmbcs.h',
	'tools/makeconv/makeconv.c',
	'tools/makeconv/makeconv.h',
	'tools/makeconv/ucnvstat.c',
      ],
      'libraries': [
	'-ldl'
      ]
    },
    {
      'target_name': 'genrb',
      'type': 'executable',
      'toolsets': [ 'host' ],
      'dependencies': [
	'tool_utils',
	'icuio',
	'icui18n',
	'icuuc',
	'icudata'
       ],
      'sources': [
	'tools/genrb/errmsg.c',
	'tools/genrb/errmsg.h',
	'tools/genrb/genrb.1.in',
	'tools/genrb/genrb.c',
	'tools/genrb/genrb.h',
	'tools/genrb/parse.cpp',
	'tools/genrb/parse.h',
	'tools/genrb/prscmnts.cpp',
	'tools/genrb/prscmnts.h',
	'tools/genrb/rbutil.c',
	'tools/genrb/rbutil.h',
	'tools/genrb/read.c',
	'tools/genrb/read.h',
	'tools/genrb/reslist.c',
	'tools/genrb/reslist.h',
	'tools/genrb/rle.c',
	'tools/genrb/rle.h',
	'tools/genrb/ustr.c',
	'tools/genrb/ustr.h',
	'tools/genrb/wrtjava.c',
	'tools/genrb/wrtxml.cpp',
      ],
      'libraries': [
	'-ldl'
      ]
    },
    {
      'target_name': 'derb',
      'type': 'executable',
      'toolsets': [ 'host' ],
      'dependencies': [
	'tool_utils',
	'icuio',
	'icui18n',
	'icuuc',
	'icudata'
       ],
      'sources': [
	'tools/genrb/derb.c',
      ],
      'libraries': [
	'-ldl',
	'-lstdc++'
      ]
    },
    {
      'target_name': 'genccode',
      'type': 'executable',
      'toolsets': [ 'host' ],
      'dependencies': [
	'tool_utils',
	'icuio',
	'icui18n',
	'icuuc',
	'icudata'
       ],
      'sources': [
	'tools/genccode/genccode.c',
      ],
      'libraries': [
	'-ldl',
	'-lstdc++'
      ]
    },
    {
      'target_name': 'gencmn',
      'type': 'executable',
      'toolsets': [ 'host' ],
      'dependencies': [
	'tool_utils',
	'icuio',
	'icui18n',
	'icuuc',
	'icudata'
       ],
      'sources': [
	'tools/gencmn/gencmn.c',
      ],
      'libraries': [
	'-ldl',
	'-lstdc++'
      ]
    },
    {
      'target_name': 'gencnval',
      'type': 'executable',
      'toolsets': [ 'host' ],
      'dependencies': [
	'tool_utils',
	'icuio',
	'icui18n',
	'icuuc',
	'icudata'
       ],
      'sources': [
	'tools/gencnval/gencnval.c',
      ],
      'libraries': [
	'-ldl',
	'-lstdc++'
      ]
    },
    {
      'target_name': 'gendict',
      'type': 'executable',
      'toolsets': [ 'host' ],
      'dependencies': [
	'tool_utils',
	'icuio',
	'icui18n',
	'icuuc',
	'icudata'
       ],
      'sources': [
	'tools/gendict/gendict.cpp',
      ],
      'libraries': [
	'-ldl',
	'-lstdc++'
      ]
    },
    {
      'target_name': 'gentest',
      'type': 'executable',
      'toolsets': [ 'host' ],
      'dependencies': [
	'tool_utils',
	'icuio',
	'icui18n',
	'icuuc',
	'icudata'
       ],
      'sources': [
	'tools/gentest/genres32.c',
	'tools/gentest/gentest.h',
	'tools/gentest/gentest.c',
      ],
      'libraries': [
	'-ldl',
	'-lstdc++'
      ]
    },
    {
      'target_name': 'gennorm2',
      'type': 'executable',
      'toolsets': [ 'host' ],
      'dependencies': [
	'tool_utils',
	'icuio',
	'icui18n',
	'icuuc',
	'icudata'
       ],
      'sources': [
	'tools/gennorm2/gennorm2.cpp',
	'tools/gennorm2/n2builder.cpp',
	'tools/gennorm2/n2builder.h',
      ],
      'libraries': [
	'-ldl',
	'-lstdc++'
      ]
    },
    {
      'target_name': 'genbrk',
      'type': 'executable',
      'toolsets': [ 'host' ],
      'dependencies': [
	'tool_utils',
	'icuio',
	'icui18n',
	'icuuc',
	'icudata'
       ],
      'sources': [
	'tools/genbrk/genbrk.cpp',
      ],
      'libraries': [
	'-ldl',
	'-lstdc++'
      ]
    },
    {
      'target_name': 'gensprep',
      'type': 'executable',
      'toolsets': [ 'host' ],
      'dependencies': [
	'tool_utils',
	'icuio',
	'icui18n',
	'icuuc',
	'icudata'
       ],
      'sources': [
	'tools/gensprep/gensprep.c',
	'tools/gensprep/gensprep.h',
	'tools/gensprep/store.c',
      ],
      'libraries': [
	'-ldl',
	'-lstdc++'
      ]
    },
    {
      'target_name': 'icuinfo',
      'type': 'executable',
      'toolsets': [ 'host' ],
      'dependencies': [
	'tool_utils',
	'icuio',
	'icui18n',
	'icuuc',
	'icudata'
       ],
      'sources': [
	'tools/icuinfo/icuinfo.cpp',
      ],
      'libraries': [
	'-ldl',
	'-lstdc++'
      ]
    },
    {
      'target_name': 'icupkg',
      'type': 'executable',
      'toolsets': [ 'host' ],
      'dependencies': [
	'tool_utils',
	'icuio',
	'icui18n',
	'icuuc',
	'icudata'
       ],
      'sources': [
	'tools/icupkg/icupkg.cpp',
      ],
      'libraries': [
	'-ldl',
	'-lstdc++'
      ]
    },
    {
      'target_name': 'icuswap',
      'type': 'executable',
      'toolsets': [ 'host' ],
      'dependencies': [
	'tool_utils',
	'icuio',
	'icui18n',
	'icuuc',
	'icudata'
       ],
      'sources': [
	'tools/icuswap/icuswap.cpp',
      ],
      'libraries': [
	'-ldl',
	'-lstdc++'
      ]
    },
    {
      'target_name': 'pkgdata',
      'type': 'executable',
      'toolsets': [ 'host' ],
      'dependencies': [
	'tool_utils',
	'icuio',
	'icui18n',
	'icuuc',
	'icudata'
       ],
      'sources': [
	'tools/pkgdata/pkgdata.cpp',
	'tools/pkgdata/pkgtypes.c',
	'tools/pkgdata/pkgtypes.h',
      ],
      'libraries': [
	'-ldl',
	'-lstdc++'
      ]
    },
    {
      'target_name': 'gencfu',
      'type': 'executable',
      'toolsets': [ 'host' ],
      'dependencies': [
	'tool_utils',
	'icuio',
	'icui18n',
	'icuuc',
	'icudata'
       ],
      'sources': [
	'tools/gencfu/gencfu.cpp',
      ],
      'libraries': [
	'-ldl',
	'-lstdc++'
      ]
    }
  ]
}
