#define wWinMain aeroSimGuiEntry
#include "app.c"
#undef wWinMain
#undef NDEBUG
#include <assert.h>
static void put(const wchar_t *p,const char *s){FILE *f=_wfopen(p,L"wb");assert(f);fwrite(s,1,strlen(s),f);fclose(f);}
int wmain(void){
 wchar_t temp[PCAP],root[PCAP],source[PCAP],wrapper[PCAP],pkg[PCAP],file[PCAP],dest[PCAP],error[2048];
 GetTempPathW(PCAP,temp);wchar_t suffix[100];swprintf(suffix,100,L"AeroSimTests-%lu",GetCurrentProcessId());pathjoin(root,temp,suffix);assert(CreateDirectoryW(root,NULL));
 pathjoin(datadir,root,L"Data");assert(CreateDirectoryW(datadir,NULL));pathjoin(logpath,datadir,L"test.log");pathjoin(cfg.community,root,L"Community");assert(CreateDirectoryW(cfg.community,NULL));
 pathjoin(source,root,L"Source");assert(CreateDirectoryW(source,NULL));pathjoin(wrapper,source,L"wrapper");assert(CreateDirectoryW(wrapper,NULL));pathjoin(pkg,wrapper,L"test-addon");assert(CreateDirectoryW(pkg,NULL));
 pathjoin(file,pkg,L"manifest.json");put(file,"{\"title\":\"Aero \\u00e9tude \\\"test\\\"\",\"creator\":\"Theo\",\"package_version\":\"1.2\"}");
 pathjoin(file,pkg,L"payload.txt");put(file,"original content");
 Job j={0};int found=0;assert(findpackages(&j,source,0,NULL,&found));assert(found==1&&j.installed==1&&j.skipped==0);
 pathjoin(dest,cfg.community,L"test-addon");assert(isdir(dest));pathjoin(file,dest,L"payload.txt");assert(exists(file));
 Addon a={0};a.path=dest;metadata(&a);assert(!wcscmp(a.title,L"Aero étude \"test\""));assert(!wcscmp(a.creator,L"Theo"));assert(!wcscmp(a.version,L"1.2"));
 put(file,"keep existing");found=0;assert(findpackages(&j,source,0,NULL,&found));assert(j.installed==1&&j.skipped==1);char content[30]={0};FILE *f=_wfopen(file,L"rb");assert(f);fread(content,1,29,f);fclose(f);assert(!strcmp(content,"keep existing"));
 wchar_t orig[PCAP];pathjoin(orig,pkg,L"payload.txt");assert(exists(orig));assert(safetree(pkg,0,error));
 assert(inpath(L"C:\\Community\\addon",L"c:\\community"));assert(!inpath(L"C:\\Community-other",L"C:\\Community"));
 wchar_t disabled[PCAP];disabledroot(disabled);assert(CreateDirectoryW(disabled,NULL));wchar_t moved[PCAP];pathjoin(moved,disabled,L"test-addon");assert(MoveFileW(dest,moved));assert(!exists(dest)&&exists(moved));assert(MoveFileW(moved,dest));assert(exists(dest));
 wchar_t link[PCAP];pathjoin(link,source,L"linked");if(CreateSymbolicLinkW(link,pkg,SYMBOLIC_LINK_FLAG_DIRECTORY|2)){assert(!safetree(link,0,error));RemoveDirectoryW(link);}else printf("SKIP: symlink fixture unavailable\n");
 wchar_t json[256];jsonstring("{\"title\":\"a\\nb\"}","title",json,256);assert(!wcscmp(json,L"a b"));
 Addon plane={0},scene={0};wcscpy(plane.type,L"AIRCRAFT");wcscpy(scene.type,L"SCENERY");assert(addoncategory(&plane)==1&&addoncategory(&scene)==3);wcscpy(plane.title,L"Alpha");wcscpy(scene.title,L"Zulu");sortColumn=1;sortDescending=0;assert(compareaddon(&plane,&scene)<0);sortDescending=1;assert(compareaddon(&plane,&scene)>0);sortColumn=5;sortDescending=0;plane.active=1;scene.active=0;assert(compareaddon(&plane,&scene)<0);
assert(contrast(readable(RGB(0,0,0),RGB(24,33,48)),RGB(24,33,48))>=4.5);assert(contrast(readable(RGB(255,255,255),RGB(255,255,255)),RGB(255,255,255))>=4.5);assert(contrast(readable(RGB(0,112,245),RGB(24,33,48)),RGB(24,33,48))>=4.5);
removetree(root);assert(!exists(root));printf("PASS: nested import, metadata, duplicates, preserved source, path boundaries, move/reactivate, JSON escapes, cleanup.\n");return 0;
}
