project('icu', [ 'cpp', 'c' ],
        version: '53.1.0',
        default_options : ['c_std=c11', 'cpp_std=c++11'])

c_compiler = meson.get_compiler('c')

dl_dep = c_compiler.find_library('dl', required : false)

lib_c_args = []

lib_cpp_args = [
    '-frtti',
    '-fno-exceptions',
    '--std=c++11',
]

lib_defines = [
    '-DU_DISABLE_RENAMING=1',

    # FIXME: make conditional...
    '-DU_HAVE_ATOMIC=1',

    '-DPACKAGE="International Components for Unicode"',
    '-DPACKAGE_BUGREPORT="http://icu-project.org/bugs"',
    '-DPACKAGE_NAME="ICU"',
    '-DPACKAGE_STRING="ICU 53.1.0"',
    '-DPACKAGE_TARNAME="International Components for Unicode"',
    '-DPACKAGE_URL="http://icu-project.org"',
    '-DPACKAGE_VERSION="53.1.0"',
    '-DSTDC_HEADERS=1',
]

if get_option('default_library') == 'shared'
    lib_defines += [ '-DPIC' ]
else
    lib_defines += [ '-DU_STATIC_IMPLEMENTATION' ]
endif

check_headers = [
    'dirent.h',
    'dlfcn.h',
    'elf.h',
    'inttypes.h',
    'memory.h',
    'stdint.h',
    'stdlib.h',
    'strings.h',
    'string.h',
    'sys/stat.h',
    'sys/types.h',
    'unistd.h',
]

foreach h : check_headers
  if c_compiler.has_header(h)
    h_vec = h.split('.')
    h = '_'.join(h_vec)
    h_vec = h.split('/')
    h = '_'.join(h_vec)
    def = 'HAVE_' + h.to_upper()
    lib_defines += '-D' + def + '=1'
  endif
endforeach

if c_compiler.has_header('elf.h')
    lib_defines += '-DU_HAVE_ELF_H'
endif

check_funcs = [
    'gettimeofday',
]

foreach f : check_funcs
  if c_compiler.has_function(f)
    def = 'HAVE_' + f.to_upper()
    lib_defines += '-D' + def + '=1'
  endif
endforeach

if dl_dep.found()
    lib_defines += '-DHAVE_DLOPEN=1'
endif

tool_inc = include_directories('source/common', 'source/i18n')


##################
#
#  I C U D A T A
#
##################

icudata_deps = []
icudata_inc = include_directories('source', 'source/common')
icudata_defines = []
icudata_src = [ 'source/stubdata/stubdata.c' ]

icudata_lib = library('icudata', icudata_src,
                      cpp_args: lib_cpp_args + lib_defines + icudata_defines,
                      c_args: lib_c_args + lib_defines + icudata_defines,
                      include_directories: [ icudata_inc ],
                      dependencies: icudata_deps)
icudata_dep = declare_dependency(link_with: icudata_lib)


##############
#
#  I C U U C
#
##############

icuuc_deps = []
icuuc_deps += icudata_dep
icuuc_deps += dl_dep

icuuc_inc = include_directories('source')
public_icuuc_includes = include_directories('source/common')

icuuc_defines = [ '-DU_COMMON_IMPLEMENTATION' ]
public_icuuc_defines = [ '-DU_DISABLE_RENAMING=1' ]

icuuc_src = [
    'source/common/errorcode.cpp',
    'source/common/putil.cpp',
    'source/common/umath.c',
    'source/common/utypes.c',
    'source/common/uinvchar.c',
    'source/common/umutex.cpp',
    'source/common/ucln_cmn.c',
    'source/common/uinit.cpp',
    'source/common/uobject.cpp',
    'source/common/cmemory.c',
    'source/common/charstr.cpp',
    'source/common/udata.cpp',
    'source/common/ucmndata.c',
    'source/common/udatamem.c',
    'source/common/umapfile.c',
    'source/common/udataswp.c',
    'source/common/ucol_swp.cpp',
    'source/common/utrace.c',
    'source/common/uhash.c',
    'source/common/uhash_us.cpp',
    'source/common/uenum.c',
    'source/common/ustrenum.cpp',
    'source/common/uvector.cpp',
    'source/common/ustack.cpp',
    'source/common/uvectr32.cpp',
    'source/common/uvectr64.cpp',
    'source/common/ucnv.c',
    'source/common/ucnv_bld.cpp',
    'source/common/ucnv_cnv.c',
    'source/common/ucnv_io.cpp',
    'source/common/ucnv_cb.c',
    'source/common/ucnv_err.c',
    'source/common/ucnvlat1.c',
    'source/common/ucnv_u7.c',
    'source/common/ucnv_u8.c',
    'source/common/ucnv_u16.c',
    'source/common/ucnv_u32.c',
    'source/common/ucnvscsu.c',
    'source/common/ucnvbocu.cpp',
    'source/common/ucnv_ext.cpp',
    'source/common/ucnvmbcs.c',
    'source/common/ucnv2022.cpp',
    'source/common/ucnvhz.c',
    'source/common/ucnv_lmb.c',
    'source/common/ucnvisci.c',
    'source/common/ucnvdisp.c',
    'source/common/ucnv_set.c',
    'source/common/ucnv_ct.c',
    'source/common/uresbund.cpp',
    'source/common/ures_cnv.c',
    'source/common/uresdata.c',
    'source/common/resbund.cpp',
    'source/common/resbund_cnv.cpp',
    'source/common/messagepattern.cpp',
    'source/common/ucat.c',
    'source/common/locmap.c',
    'source/common/uloc.cpp',
    'source/common/locid.cpp',
    'source/common/locutil.cpp',
    'source/common/locavailable.cpp',
    'source/common/locdispnames.cpp',
    'source/common/loclikely.cpp',
    'source/common/locresdata.cpp',
    'source/common/bytestream.cpp',
    'source/common/stringpiece.cpp',
    'source/common/stringtriebuilder.cpp',
    'source/common/bytestriebuilder.cpp',
    'source/common/bytestrie.cpp',
    'source/common/bytestrieiterator.cpp',
    'source/common/ucharstrie.cpp',
    'source/common/ucharstriebuilder.cpp',
    'source/common/ucharstrieiterator.cpp',
    'source/common/dictionarydata.cpp',
    'source/common/appendable.cpp',
    'source/common/ustr_cnv.c',
    'source/common/unistr_cnv.cpp',
    'source/common/unistr.cpp',
    'source/common/unistr_case.cpp',
    'source/common/unistr_props.cpp',
    'source/common/utf_impl.c',
    'source/common/ustring.cpp',
    'source/common/ustrcase.cpp',
    'source/common/ucasemap.cpp',
    'source/common/ucasemap_titlecase_brkiter.cpp',
    'source/common/cstring.c',
    'source/common/ustrfmt.c',
    'source/common/ustrtrns.cpp',
    'source/common/ustr_wcs.cpp',
    'source/common/utext.cpp',
    'source/common/unistr_case_locale.cpp',
    'source/common/ustrcase_locale.cpp',
    'source/common/unistr_titlecase_brkiter.cpp',
    'source/common/ustr_titlecase_brkiter.cpp',
    'source/common/normalizer2impl.cpp',
    'source/common/normalizer2.cpp',
    'source/common/filterednormalizer2.cpp',
    'source/common/normlzr.cpp',
    'source/common/unorm.cpp',
    'source/common/unormcmp.cpp',
    'source/common/chariter.cpp',
    'source/common/schriter.cpp',
    'source/common/uchriter.cpp',
    'source/common/uiter.cpp',
    'source/common/patternprops.cpp',
    'source/common/uchar.c',
    'source/common/uprops.cpp',
    'source/common/ucase.cpp',
    'source/common/propname.cpp',
    'source/common/ubidi_props.c',
    'source/common/ubidi.c',
    'source/common/ubidiwrt.c',
    'source/common/ubidiln.c',
    'source/common/ushape.cpp',
    'source/common/uscript.c',
    'source/common/uscript_props.cpp',
    'source/common/usc_impl.c',
    'source/common/unames.cpp',
    'source/common/utrie.cpp',
    'source/common/utrie2.cpp',
    'source/common/utrie2_builder.cpp',
    'source/common/bmpset.cpp',
    'source/common/unisetspan.cpp',
    'source/common/uset_props.cpp',
    'source/common/uniset_props.cpp',
    'source/common/uniset_closure.cpp',
    'source/common/uset.cpp',
    'source/common/uniset.cpp',
    'source/common/usetiter.cpp',
    'source/common/ruleiter.cpp',
    'source/common/caniter.cpp',
    'source/common/unifilt.cpp',
    'source/common/unifunct.cpp',
    'source/common/uarrsort.c',
    'source/common/brkiter.cpp',
    'source/common/ubrk.cpp',
    'source/common/brkeng.cpp',
    'source/common/dictbe.cpp',
    'source/common/rbbi.cpp',
    'source/common/rbbidata.cpp',
    'source/common/rbbinode.cpp',
    'source/common/rbbirb.cpp',
    'source/common/rbbiscan.cpp',
    'source/common/rbbisetb.cpp',
    'source/common/rbbistbl.cpp',
    'source/common/rbbitblb.cpp',
    'source/common/serv.cpp',
    'source/common/servnotf.cpp',
    'source/common/servls.cpp',
    'source/common/servlk.cpp',
    'source/common/servlkf.cpp',
    'source/common/servrbf.cpp',
    'source/common/servslkf.cpp',
    'source/common/uidna.cpp',
    'source/common/usprep.cpp',
    'source/common/uts46.cpp',
    'source/common/punycode.cpp',
    'source/common/util.cpp',
    'source/common/util_props.cpp',
    'source/common/parsepos.cpp',
    'source/common/locbased.cpp',
    'source/common/cwchar.c',
    'source/common/wintz.c',
    'source/common/dtintrv.cpp',
    'source/common/ucnvsel.cpp',
    'source/common/propsvec.c',
    'source/common/ulist.c',
    'source/common/uloc_tag.c',
    'source/common/icudataver.c',
    'source/common/icuplug.c',
    'source/common/listformatter.cpp',
    'source/common/lrucache.cpp',
    'source/common/sharedobject.cpp',
    'source/common/simplepatternformatter.cpp',
]

icuuc_lib = library('icuuc', icuuc_src,
                    cpp_args: lib_cpp_args + lib_defines + icuuc_defines + public_icuuc_defines,
                    c_args: lib_c_args + lib_defines + icuuc_defines + public_icuuc_defines,
                    include_directories: [ icuuc_inc, public_icuuc_includes ],
                    dependencies: icuuc_deps)
icuuc_dep = declare_dependency(link_with: icuuc_lib,
                               compile_args: public_icuuc_defines,
                               include_directories: public_icuuc_includes)


##################
#
#  I C U I 1 8 N
#
##################

icui18n_deps = []
icui18n_deps += icuuc_dep

icui18n_inc = include_directories(
    'source',
    'source/common',
    'source/i18n',
    'source/i18n/unicode')
icui18n_defines = [ '-DU_I18N_IMPLEMENTATION' ]

icui18n_src = [
    'source/i18n/dangical.cpp',
    'source/i18n/sharedpluralrules.h',
    'source/i18n/tzrule.cpp',
    'source/i18n/ethpccal.cpp',
    'source/i18n/decNumber.h',
    'source/i18n/nfrule.cpp',
    'source/i18n/regexst.h',
    'source/i18n/strmatch.h',
    'source/i18n/uregion.cpp',
    'source/i18n/ztrans.h',
    'source/i18n/regeximp.h',
    'source/i18n/simpletz.cpp',
    'source/i18n/ucol_imp.h',
    'source/i18n/utf8collationiterator.h',
    'source/i18n/uregexc.cpp',
    'source/i18n/tmutfmt.cpp',
    'source/i18n/collationfastlatin.h',
    'source/i18n/wintzimpl.cpp',
    'source/i18n/buddhcal.cpp',
    'source/i18n/fmtable_cnv.cpp',
    'source/i18n/uspoof_conf.cpp',
    'source/i18n/regeximp.cpp',
    'source/i18n/ucoleitr.cpp',
    'source/i18n/collationrootelements.cpp',
    'source/i18n/ucol_res.cpp',
    'source/i18n/indiancal.h',
    'source/i18n/tztrans.cpp',
    'source/i18n/buddhcal.h',
    'source/i18n/dangical.h',
    'source/i18n/transreg.h',
    'source/i18n/wintzimpl.h',
    'source/i18n/collationiterator.h',
    'source/i18n/cpdtrans.h',
    'source/i18n/cecal.h',
    'source/i18n/collationfcd.h',
    'source/i18n/collation.h',
    'source/i18n/decNumber.c',
    'source/i18n/rbt_rule.h',
    'source/i18n/nfrs.h',
    'source/i18n/brktrans.h',
    'source/i18n/plurrule_impl.h',
    'source/i18n/uitercollationiterator.cpp',
    'source/i18n/nultrans.cpp',
    'source/i18n/nfrs.cpp',
    'source/i18n/nortrans.cpp',
    'source/i18n/ucsdet.cpp',
    'source/i18n/collationroot.cpp',
    'source/i18n/cecal.cpp',
    'source/i18n/collationbasedatabuilder.cpp',
    'source/i18n/regextxt.cpp',
    'source/i18n/anytrans.h',
    'source/i18n/rbt.cpp',
    'source/i18n/tmutamt.cpp',
    'source/i18n/quantityformatter.cpp',
    'source/i18n/numsys.cpp',
    'source/i18n/zonemeta.cpp',
    'source/i18n/nfsubs.h',
    'source/i18n/unesctrn.cpp',
    'source/i18n/regexcmp.h',
    'source/i18n/selfmt.cpp',
    'source/i18n/esctrn.cpp',
    'source/i18n/collationdatareader.cpp',
    'source/i18n/uspoof_conf.h',
    'source/i18n/currunit.cpp',
    'source/i18n/nortrans.h',
    'source/i18n/region.cpp',
    'source/i18n/ztrans.cpp',
    'source/i18n/tznames_impl.h',
    'source/i18n/msgfmt_impl.h',
    'source/i18n/rulebasedcollator.cpp',
    'source/i18n/coptccal.cpp',
    'source/i18n/region_impl.h',
    'source/i18n/ucal.cpp',
    'source/i18n/decfmtst.cpp',
    'source/i18n/decNumberLocal.h',
    'source/i18n/taiwncal.cpp',
    'source/i18n/nultrans.h',
    'source/i18n/upluralrules.cpp',
    'source/i18n/inputext.h',
    'source/i18n/uni2name.h',
    'source/i18n/coptccal.h',
    'source/i18n/fmtableimp.h',
    'source/i18n/collationcompare.cpp',
    'source/i18n/unum.cpp',
    'source/i18n/uni2name.cpp',
    'source/i18n/umsg_imp.h',
    'source/i18n/search.cpp',
    'source/i18n/windtfmt.cpp',
    'source/i18n/selfmtimpl.h',
    'source/i18n/collationkeys.h',
    'source/i18n/gregocal.cpp',
    'source/i18n/islamcal.cpp',
    'source/i18n/tridpars.cpp',
    'source/i18n/zrule.cpp',
    'source/i18n/smpdtfst.h',
    'source/i18n/hebrwcal.h',
    'source/i18n/rbt_rule.cpp',
    'source/i18n/reldtfmt.cpp',
    'source/i18n/coleitr.cpp',
    'source/i18n/zonemeta.h',
    'source/i18n/tznames_impl.cpp',
    'source/i18n/collationdatareader.h',
    'source/i18n/tzgnames.cpp',
    'source/i18n/astro.h',
    'source/i18n/collation.cpp',
    'source/i18n/dtitvinf.cpp',
    'source/i18n/gregoimp.cpp',
    'source/i18n/unicode/udisplaycontext.h',
    'source/i18n/unicode/smpdtfmt.h',
    'source/i18n/unicode/datefmt.h',
    'source/i18n/unicode/ucol.h',
    'source/i18n/unicode/locdspnm.h',
    'source/i18n/unicode/choicfmt.h',
    'source/i18n/unicode/rbtz.h',
    'source/i18n/unicode/dtrule.h',
    'source/i18n/unicode/fpositer.h',
    'source/i18n/unicode/dtitvinf.h',
    'source/i18n/unicode/umsg.h',
    'source/i18n/unicode/tztrans.h',
    'source/i18n/unicode/selfmt.h',
    'source/i18n/unicode/dtptngen.h',
    'source/i18n/unicode/ucoleitr.h',
    'source/i18n/unicode/rbnf.h',
    'source/i18n/unicode/curramt.h',
    'source/i18n/unicode/ucal.h',
    'source/i18n/unicode/region.h',
    'source/i18n/unicode/vtzone.h',
    'source/i18n/unicode/format.h',
    'source/i18n/unicode/decimfmt.h',
    'source/i18n/unicode/simpletz.h',
    'source/i18n/unicode/usearch.h',
    'source/i18n/unicode/numfmt.h',
    'source/i18n/unicode/msgfmt.h',
    'source/i18n/unicode/timezone.h',
    'source/i18n/unicode/fieldpos.h',
    'source/i18n/unicode/gregocal.h',
    'source/i18n/unicode/tmutamt.h',
    'source/i18n/unicode/unumsys.h',
    'source/i18n/unicode/upluralrules.h',
    'source/i18n/unicode/udat.h',
    'source/i18n/unicode/translit.h',
    'source/i18n/unicode/fmtable.h',
    'source/i18n/unicode/uregion.h',
    'source/i18n/unicode/ucsdet.h',
    'source/i18n/unicode/measunit.h',
    'source/i18n/unicode/unum.h',
    'source/i18n/unicode/dtfmtsym.h',
    'source/i18n/unicode/uformattable.h',
    'source/i18n/unicode/ugender.h',
    'source/i18n/unicode/utmscale.h',
    'source/i18n/unicode/uregex.h',
    'source/i18n/unicode/alphaindex.h',
    'source/i18n/unicode/search.h',
    'source/i18n/unicode/tznames.h',
    'source/i18n/unicode/calendar.h',
    'source/i18n/unicode/udateintervalformat.h',
    'source/i18n/unicode/reldatefmt.h',
    'source/i18n/unicode/dcfmtsym.h',
    'source/i18n/unicode/uspoof.h',
    'source/i18n/unicode/currunit.h',
    'source/i18n/unicode/measure.h',
    'source/i18n/unicode/unirepl.h',
    'source/i18n/unicode/ucurr.h',
    'source/i18n/unicode/uldnames.h',
    'source/i18n/unicode/udatpg.h',
    'source/i18n/unicode/utrans.h',
    'source/i18n/unicode/dtitvfmt.h',
    'source/i18n/unicode/compactdecimalformat.h',
    'source/i18n/unicode/coll.h',
    'source/i18n/unicode/basictz.h',
    'source/i18n/unicode/sortkey.h',
    'source/i18n/unicode/tzrule.h',
    'source/i18n/unicode/gender.h',
    'source/i18n/unicode/regex.h',
    'source/i18n/unicode/tzfmt.h',
    'source/i18n/unicode/tmunit.h',
    'source/i18n/unicode/filteredbrk.h',
    'source/i18n/unicode/ulocdata.h',
    'source/i18n/unicode/tmutfmt.h',
    'source/i18n/unicode/plurfmt.h',
    'source/i18n/unicode/tblcoll.h',
    'source/i18n/unicode/measfmt.h',
    'source/i18n/unicode/stsearch.h',
    'source/i18n/unicode/currpinf.h',
    'source/i18n/unicode/coleitr.h',
    'source/i18n/unicode/numsys.h',
    'source/i18n/unicode/plurrule.h',
    'source/i18n/quant.h',
    'source/i18n/fphdlimp.cpp',
    'source/i18n/udat.cpp',
    'source/i18n/olsontz.h',
    'source/i18n/nfrlist.h',
    'source/i18n/winnmfmt.cpp',
    'source/i18n/sortkey.cpp',
    'source/i18n/utf16collationiterator.cpp',
    'source/i18n/currfmt.h',
    'source/i18n/dcfmtimp.h',
    'source/i18n/csdetect.cpp',
    'source/i18n/regextxt.h',
    'source/i18n/ucln_in.h',
    'source/i18n/format.cpp',
    'source/i18n/indiancal.cpp',
    'source/i18n/csrmbcs.h',
    'source/i18n/collationtailoring.cpp',
    'source/i18n/csmatch.cpp',
    'source/i18n/collationdata.h',
    'source/i18n/csrutf8.cpp',
    'source/i18n/tzgnames.h',
    'source/i18n/toupptrn.cpp',
    'source/i18n/ucln_in.c',
    'source/i18n/chnsecal.cpp',
    'source/i18n/ucurr.cpp',
    'source/i18n/ulocdata.c',
    'source/i18n/chnsecal.h',
    'source/i18n/csrmbcs.cpp',
    'source/i18n/quant.cpp',
    'source/i18n/digitlst.cpp',
    'source/i18n/unesctrn.h',
    'source/i18n/timezone.cpp',
    'source/i18n/ucurrimp.h',
    'source/i18n/rbtz.cpp',
    'source/i18n/collationsettings.h',
    'source/i18n/collationcompare.h',
    'source/i18n/ucol_sit.cpp',
    'source/i18n/rbt_data.cpp',
    'source/i18n/rematch.cpp',
    'source/i18n/csrecog.cpp',
    'source/i18n/utf16collationiterator.h',
    'source/i18n/collationfastlatinbuilder.h',
    'source/i18n/measunit.cpp',
    'source/i18n/quantityformatter.h',
    'source/i18n/utrans.cpp',
    'source/i18n/tmunit.cpp',
    'source/i18n/udatpg.cpp',
    'source/i18n/remtrans.cpp',
    'source/i18n/japancal.h',
    'source/i18n/filteredbrk.cpp',
    'source/i18n/numfmt.cpp',
    'source/i18n/bocsu.h',
    'source/i18n/unumsys.cpp',
    'source/i18n/digitlst.h',
    'source/i18n/regexcmp.cpp',
    'source/i18n/collationroot.h',
    'source/i18n/taiwncal.h',
    'source/i18n/utmscale.c',
    'source/i18n/tzfmt.cpp',
    'source/i18n/japancal.cpp',
    'source/i18n/reldtfmt.h',
    'source/i18n/calendar.cpp',
    'source/i18n/curramt.cpp',
    'source/i18n/anytrans.cpp',
    'source/i18n/collationkeys.cpp',
    'source/i18n/toupptrn.h',
    'source/i18n/casetrn.h',
    'source/i18n/collationdatawriter.cpp',
    'source/i18n/funcrepl.cpp',
    'source/i18n/tolowtrn.cpp',
    'source/i18n/measfmt.cpp',
    'source/i18n/udateintervalformat.cpp',
    'source/i18n/csrucode.h',
    'source/i18n/scriptset.cpp',
    'source/i18n/rbt_pars.cpp',
    'source/i18n/datefmt.cpp',
    'source/i18n/dtitv_impl.h',
    'source/i18n/collationrootelements.h',
    'source/i18n/name2uni.cpp',
    'source/i18n/dtitvfmt.cpp',
    'source/i18n/tolowtrn.h',
    'source/i18n/collationdata.cpp',
    'source/i18n/collationweights.h',
    'source/i18n/dtptngen_impl.h',
    'source/i18n/winnmfmt.h',
    'source/i18n/casetrn.cpp',
    'source/i18n/dtrule.cpp',
    'source/i18n/hebrwcal.cpp',
    'source/i18n/remtrans.h',
    'source/i18n/nfsubs.cpp',
    'source/i18n/rbt_data.h',
    'source/i18n/identifier_info.h',
    'source/i18n/uspoof_wsconf.cpp',
    'source/i18n/basictz.cpp',
    'source/i18n/csrsbcs.h',
    'source/i18n/collationsettings.cpp',
    'source/i18n/cpdtrans.cpp',
    'source/i18n/csr2022.cpp',
    'source/i18n/decContext.c',
    'source/i18n/esctrn.h',
    'source/i18n/tznames.cpp',
    'source/i18n/uregex.cpp',
    'source/i18n/plurfmt.cpp',
    'source/i18n/collationdatabuilder.cpp',
    'source/i18n/collationsets.h',
    'source/i18n/tridpars.h',
    'source/i18n/sharednumberformat.h',
    'source/i18n/rbnf.cpp',
    'source/i18n/nfrule.h',
    'source/i18n/identifier_info.cpp',
    'source/i18n/ethpccal.h',
    'source/i18n/rbt_set.h',
    'source/i18n/coll.cpp',
    'source/i18n/translit.cpp',
    'source/i18n/collationweights.cpp',
    'source/i18n/collationsets.cpp',
    'source/i18n/strmatch.cpp',
    'source/i18n/fpositer.cpp',
    'source/i18n/uspoof_impl.cpp',
    'source/i18n/olsontz.cpp',
    'source/i18n/decfmtst.h',
    'source/i18n/titletrn.h',
    'source/i18n/brktrans.cpp',
    'source/i18n/decimfmt.cpp',
    'source/i18n/titletrn.cpp',
    'source/i18n/collationdatabuilder.h',
    'source/i18n/transreg.cpp',
    'source/i18n/decContext.h',
    'source/i18n/currpinf.cpp',
    'source/i18n/gender.cpp',
    'source/i18n/csrecog.h',
    'source/i18n/vzone.cpp',
    'source/i18n/usrchimp.h',
    'source/i18n/gregoimp.h',
    'source/i18n/uspoof_impl.h',
    'source/i18n/rbt.h',
    'source/i18n/reldatefmt.cpp',
    'source/i18n/strrepl.h',
    'source/i18n/csmatch.h',
    'source/i18n/utf8collationiterator.cpp',
    'source/i18n/smpdtfst.cpp',
    'source/i18n/collationbasedatabuilder.h',
    'source/i18n/islamcal.h',
    'source/i18n/funcrepl.h',
    'source/i18n/collationfastlatin.cpp',
    'source/i18n/collationruleparser.h',
    'source/i18n/fmtable.cpp',
    'source/i18n/currfmt.cpp',
    'source/i18n/collationiterator.cpp',
    'source/i18n/astro.cpp',
    'source/i18n/collationfastlatinbuilder.cpp',
    'source/i18n/dcfmtsym.cpp',
    'source/i18n/msgfmt.cpp',
    'source/i18n/rbt_pars.h',
    'source/i18n/repattrn.cpp',
    'source/i18n/umsg.cpp',
    'source/i18n/dtfmtsym.cpp',
    'source/i18n/collationruleparser.cpp',
    'source/i18n/vzone.h',
    'source/i18n/stsearch.cpp',
    'source/i18n/measure.cpp',
    'source/i18n/strrepl.cpp',
    'source/i18n/decimalformatpattern.cpp',
    'source/i18n/uitercollationiterator.h',
    'source/i18n/persncal.h',
    'source/i18n/collationbuilder.cpp',
    'source/i18n/csrutf8.h',
    'source/i18n/uspoof_wsconf.h',
    'source/i18n/csr2022.h',
    'source/i18n/rbt_set.cpp',
    'source/i18n/uspoof.cpp',
    'source/i18n/name2uni.h',
    'source/i18n/regexst.cpp',
    'source/i18n/persncal.cpp',
    'source/i18n/locdspnm.cpp',
    'source/i18n/fphdlimp.h',
    'source/i18n/csrucode.cpp',
    'source/i18n/collationfcd.cpp',
    'source/i18n/compactdecimalformat.cpp',
    'source/i18n/ucol.cpp',
    'source/i18n/dtptngen.cpp',
    'source/i18n/smpdtfmt.cpp',
    'source/i18n/collationdatawriter.h',
    'source/i18n/collationtailoring.h',
    'source/i18n/collationbuilder.h',
    'source/i18n/usearch.cpp',
    'source/i18n/zrule.h',
    'source/i18n/csdetect.h',
    'source/i18n/inputext.cpp',
    'source/i18n/choicfmt.cpp',
    'source/i18n/vtzone.cpp',
    'source/i18n/uspoof_build.cpp',
    'source/i18n/regexcst.h',
    'source/i18n/plurrule.cpp',
    'source/i18n/csrsbcs.cpp',
    'source/i18n/alphaindex.cpp',
    'source/i18n/bocsu.cpp',
    'source/i18n/numsys_impl.h',
    'source/i18n/decimalformatpattern.h',
    'source/i18n/windtfmt.h',
    'source/i18n/scriptset.h',
]

icui18n_lib = library('icui18n', icui18n_src,
                      cpp_args: lib_cpp_args + lib_defines + icui18n_defines,
                      c_args: lib_c_args + lib_defines + icui18n_defines,
                      include_directories: [ icui18n_inc ],
                      dependencies: icui18n_deps)
icui18n_dep = declare_dependency(link_with: icui18n_lib)



##############
#
#  I C U I O
#
##############

icuio_deps = []
icuio_deps += icuuc_dep
icuio_deps += icui18n_dep

icuio_inc = include_directories('source', 'source/common')
icuio_defines = [ '-DU_IO_IMPLEMENTATION' ]

icuio_src = [
    'source/io/locbund.h',
    'source/io/locbund.cpp',
    'source/io/sprintf.c',
    'source/io/sscanf.c',
    'source/io/ucln_io.c',
    'source/io/ucln_io.h',
    'source/io/ufile.c',
    'source/io/ufile.h',
    'source/io/ufmt_cmn.c',
    'source/io/ufmt_cmn.h',
    'source/io/uprintf.c',
    'source/io/uprintf.h',
    'source/io/uprntf_p.c',
    'source/io/uscanf.c',
    'source/io/uscanf.h',
    'source/io/uscanf_p.c',
    'source/io/ustdio.c',
    'source/io/ustream.cpp',
]

icuio_lib = library('icuio', icuio_src,
                    cpp_args: lib_cpp_args + lib_defines + icuio_defines,
                    c_args: lib_c_args + lib_defines + icuio_defines,
                    include_directories: [ icuio_inc ],
                    dependencies: icuio_deps)
icuio_dep = declare_dependency(link_with: icuio_lib)



##############
#
#  C T E S T
#
##############

ctestfw_deps = []
ctestfw_deps += icuuc_dep

ctestfw_inc = include_directories(
    'source',
    'source/common',
    'source/i18n',
    'source/tools/toolutil',
    'source/tools/ctestfw',
    )

ctestfw_defines = [ '-DT_CTESTFW_IMPLEMENTATION' ]

ctestfw_src = [
    'source/tools/ctestfw/unicode/ctest.h',
    'source/tools/ctestfw/ctest.c',
    'source/tools/ctestfw/unicode/datamap.h',
    'source/tools/ctestfw/datamap.cpp',
    'source/tools/ctestfw/unicode/testdata.h',
    'source/tools/ctestfw/testdata.cpp',
    'source/tools/ctestfw/unicode/testlog.h',
    'source/tools/ctestfw/unicode/testtype.h',
    'source/tools/ctestfw/unicode/tstdtmod.h',
    'source/tools/ctestfw/tstdtmod.cpp',
    'source/tools/ctestfw/unicode/uperf.h',
    'source/tools/ctestfw/uperf.cpp',
    'source/tools/ctestfw/unicode/utimer.h',
    'source/tools/ctestfw/ucln_ct.c',
]

ctestfw_lib = static_library(
        'ctestfw', ctestfw_src,
        cpp_args: lib_cpp_args + lib_defines + ctestfw_defines,
        c_args: lib_c_args + lib_defines + ctestfw_defines,
        include_directories: [ ctestfw_inc ],
        dependencies: ctestfw_deps)
ctestfw_dep = declare_dependency(link_with: ctestfw_lib)


#######################
#
#  T O O L  U T I L S
#
#######################

tool_utils_deps = []
tool_utils_deps += icuuc_dep

tool_utils_inc = include_directories(
    'source',
    'source/common',
    'source/i18n',
    'source/tools/toolutil',
    )

tool_utils_public_inc = include_directories('source/tools/toolutil')
tool_utils_defines = [ '-DU_TOOLUTIL_IMPLEMENTATION' ]

tool_utils_src = [
    'source/tools/toolutil/collationinfo.cpp',
    'source/tools/toolutil/collationinfo.h',
    'source/tools/toolutil/dbgutil.cpp',
    'source/tools/toolutil/dbgutil.h',
    'source/tools/toolutil/denseranges.cpp',
    'source/tools/toolutil/denseranges.h',
    'source/tools/toolutil/filestrm.c',
    'source/tools/toolutil/filestrm.h',
    'source/tools/toolutil/filetools.cpp',
    'source/tools/toolutil/filetools.h',
    'source/tools/toolutil/flagparser.c',
    'source/tools/toolutil/flagparser.h',
    'source/tools/toolutil/package.cpp',
    'source/tools/toolutil/package.h',
    'source/tools/toolutil/pkg_genc.c',
    'source/tools/toolutil/pkg_genc.h',
    'source/tools/toolutil/pkg_gencmn.c',
    'source/tools/toolutil/pkg_gencmn.h',
    'source/tools/toolutil/pkg_icu.cpp',
    'source/tools/toolutil/pkg_icu.h',
    'source/tools/toolutil/pkg_imp.h',
    'source/tools/toolutil/pkgitems.cpp',
    'source/tools/toolutil/ppucd.cpp',
    'source/tools/toolutil/ppucd.h',
    'source/tools/toolutil/swapimpl.cpp',
    'source/tools/toolutil/swapimpl.h',
    'source/tools/toolutil/toolutil.cpp',
    'source/tools/toolutil/toolutil.h',
    'source/tools/toolutil/ucbuf.c',
    'source/tools/toolutil/ucbuf.h',
    'source/tools/toolutil/ucln_tu.c',
    'source/tools/toolutil/ucm.c',
    'source/tools/toolutil/ucm.h',
    'source/tools/toolutil/ucmstate.c',
    'source/tools/toolutil/udbgutil.cpp',
    'source/tools/toolutil/udbgutil.h',
    'source/tools/toolutil/unewdata.c',
    'source/tools/toolutil/unewdata.h',
    'source/tools/toolutil/uoptions.c',
    'source/tools/toolutil/uoptions.h',
    'source/tools/toolutil/uparse.c',
    'source/tools/toolutil/uparse.h',
    'source/tools/toolutil/writesrc.c',
    'source/tools/toolutil/writesrc.h',
    'source/tools/toolutil/xmlparser.cpp',
    'source/tools/toolutil/xmlparser.h',
]

tool_utils_lib = static_library(
        'tool_utils', tool_utils_src,
        cpp_args: lib_cpp_args + lib_defines + tool_utils_defines,
        c_args: lib_c_args + lib_defines + tool_utils_defines,
        include_directories: [ tool_utils_inc ],
        dependencies: tool_utils_deps,
        native: true)
tool_utils_dep = declare_dependency(link_with: tool_utils_lib,
                                    include_directories: tool_utils_public_inc)


####################
#
#  T O O L S
#
####################

makeconv_src = [
    'source/tools/makeconv/gencnvex.c',
    'source/tools/makeconv/genmbcs.cpp',
    'source/tools/makeconv/genmbcs.h',
    'source/tools/makeconv/makeconv.c',
    'source/tools/makeconv/makeconv.h',
    'source/tools/makeconv/ucnvstat.c',
]
executable('makeconv', makeconv_src,
           dependencies: [ tool_utils_dep, icuio_dep, icui18n_dep, icuuc_dep, dl_dep ],
           include_directories: tool_inc,
           native: true)

genrb_src = [
    'source/tools/genrb/errmsg.c',
    'source/tools/genrb/errmsg.h',
    'source/tools/genrb/genrb.c',
    'source/tools/genrb/genrb.h',
    'source/tools/genrb/parse.cpp',
    'source/tools/genrb/parse.h',
    'source/tools/genrb/prscmnts.cpp',
    'source/tools/genrb/prscmnts.h',
    'source/tools/genrb/rbutil.c',
    'source/tools/genrb/rbutil.h',
    'source/tools/genrb/read.c',
    'source/tools/genrb/read.h',
    'source/tools/genrb/reslist.c',
    'source/tools/genrb/reslist.h',
    'source/tools/genrb/rle.c',
    'source/tools/genrb/rle.h',
    'source/tools/genrb/ustr.c',
    'source/tools/genrb/ustr.h',
    'source/tools/genrb/wrtjava.c',
    'source/tools/genrb/wrtxml.cpp',
]
executable('genrb', genrb_src,
           dependencies: [ tool_utils_dep, icuio_dep, icui18n_dep, icuuc_dep, dl_dep ],
           include_directories: tool_inc,
           native: true)


derb_src = [ 'source/tools/genrb/derb.c' ]
executable('derb', derb_src,
           dependencies: [ tool_utils_dep, icuio_dep, icui18n_dep, icuuc_dep, dl_dep ],
           include_directories: tool_inc,
           native: true)


genccode_src = [ 'source/tools/genccode/genccode.c' ]
executable('genccode', genccode_src,
           dependencies: [ tool_utils_dep, icuio_dep, icui18n_dep, icuuc_dep, dl_dep ],
           include_directories: tool_inc,
           native: true)


gencmn_src = [ 'source/tools/gencmn/gencmn.c' ]
executable('gencmn', gencmn_src,
           dependencies: [ tool_utils_dep, icuio_dep, icui18n_dep, icuuc_dep, dl_dep ],
           include_directories: tool_inc,
           native: true)


gencnval_src = [ 'source/tools/gencnval/gencnval.c' ]
executable('gencnval', gencnval_src,
           dependencies: [ tool_utils_dep, icuio_dep, icui18n_dep, icuuc_dep, dl_dep ],
           include_directories: tool_inc,
           native: true)


gendict_src = [ 'source/tools/gendict/gendict.cpp' ]
executable('gendict', gendict_src,
           dependencies: [ tool_utils_dep, icuio_dep, icui18n_dep, icuuc_dep, dl_dep ],
           include_directories: tool_inc,
           native: true)


gentest_src = [
    'source/tools/gentest/genres32.c',
    'source/tools/gentest/gentest.h',
    'source/tools/gentest/gentest.c',
]
executable('gentest', gentest_src,
           dependencies: [ tool_utils_dep, icuio_dep, icui18n_dep, icuuc_dep, dl_dep ],
           include_directories: tool_inc,
           native: true)


gennorm2_src = [
    'source/tools/gennorm2/gennorm2.cpp',
    'source/tools/gennorm2/n2builder.cpp',
    'source/tools/gennorm2/n2builder.h',
]
executable('gennorm2', gennorm2_src,
           dependencies: [ tool_utils_dep, icuio_dep, icui18n_dep, icuuc_dep, dl_dep ],
           include_directories: tool_inc,
           native: true)


genbrk_src = [ 'source/tools/genbrk/genbrk.cpp' ]
executable('genbrk', genbrk_src,
           dependencies: [ tool_utils_dep, icuio_dep, icui18n_dep, icuuc_dep, dl_dep ],
           include_directories: tool_inc,
           native: true)


gensprep_src = [
    'source/tools/gensprep/gensprep.c',
    'source/tools/gensprep/gensprep.h',
    'source/tools/gensprep/store.c',
]
executable('gensprep', gensprep_src,
           dependencies: [ tool_utils_dep, icuio_dep, icui18n_dep, icuuc_dep, dl_dep ],
           include_directories: tool_inc,
           native: true)


icuinfo_src = [ 'source/tools/icuinfo/icuinfo.cpp' ]
executable('icuinfo', icuinfo_src,
           dependencies: [ tool_utils_dep, icuio_dep, icui18n_dep, icuuc_dep, dl_dep ],
           include_directories: tool_inc,
           native: true)


icupkg_src = [ 'source/tools/icupkg/icupkg.cpp' ]
executable('icupkg', icupkg_src,
           dependencies: [ tool_utils_dep, icuio_dep, icui18n_dep, icuuc_dep, dl_dep ],
           include_directories: tool_inc,
           native: true)


icuswap_src = [ 'source/tools/icuswap/icuswap.cpp' ]
executable('icuswap', icuswap_src,
           dependencies: [ tool_utils_dep, icuio_dep, icui18n_dep, icuuc_dep, dl_dep ],
           include_directories: tool_inc,
           native: true)


pkgdata_src = [
    'source/tools/pkgdata/pkgdata.cpp',
    'source/tools/pkgdata/pkgtypes.c',
    'source/tools/pkgdata/pkgtypes.h',
]
executable('pkgdata', pkgdata_src,
           dependencies: [ tool_utils_dep, icuio_dep, icui18n_dep, icuuc_dep, dl_dep ],
           include_directories: tool_inc,
           native: true)


gencfu_src = [ 'source/tools/gencfu/gencfu.cpp' ]
executable('gencfu', gencfu_src,
           dependencies: [ tool_utils_dep, icuio_dep, icui18n_dep, icuuc_dep, dl_dep ],
           include_directories: tool_inc,
           native: true)

