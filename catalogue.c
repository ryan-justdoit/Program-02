#include "header.h"
#include "common.h"
dlinklist catalogue(int argc,char **argv)
{
	// 1，确保有一个参数，并且是目录
	if(argc != 2)
	{
		printf("标准用法 %s + 目录\n",argv[0]);
		exit(0);
	}

	struct stat info;
	bzero(&info, sizeof(info));

	if(stat(argv[1], &info) == -1)
	{
		perror("获取指定文件属性失败");
		exit(0);
	}

	if((info.st_mode&S_IFMT) != S_IFDIR)
	{
		printf("给我的不是目录！走人！\n");
		exit(0);
	}

	// 2，打开目录，并循环地读取里面的目录项
	DIR *dp = opendir(argv[1]);
	chdir(argv[1]);
	struct dirent *ep;

        dlinklist head = init_list();

	while(1)
	{
		ep = readdir(dp);

		// 读完收工
		if(ep == NULL)
			break;

		// 跳过所有隐藏文件
		if(ep->d_name[0] == '.')
			continue;

                if(strstr(ep->d_name, ".mp3"))
                {
                        head = init_lianbiao(ep->d_name,head);
                }
               // printf("head->next->name2 = %s\n",head->next->name);
		// 获取当前文件的stat信息
		bzero(&info, sizeof(info));
		stat(ep->d_name, &info);

	//	printf("%s: %ld\n", ep->d_name, info.st_size);
	}

	// 3，释放相应的资源
		//closedir(dp);

	return head;
}
