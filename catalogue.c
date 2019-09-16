#include "header.h"
#include "common.h"
dlinklist catalogue(int argc,char **argv)
{
	// 1��ȷ����һ��������������Ŀ¼
	if(argc != 2)
	{
		printf("��׼�÷� %s + Ŀ¼\n",argv[0]);
		exit(0);
	}

	struct stat info;
	bzero(&info, sizeof(info));

	if(stat(argv[1], &info) == -1)
	{
		perror("��ȡָ���ļ�����ʧ��");
		exit(0);
	}

	if((info.st_mode&S_IFMT) != S_IFDIR)
	{
		printf("���ҵĲ���Ŀ¼�����ˣ�\n");
		exit(0);
	}

	// 2����Ŀ¼����ѭ���ض�ȡ�����Ŀ¼��
	DIR *dp = opendir(argv[1]);
	chdir(argv[1]);
	struct dirent *ep;

        dlinklist head = init_list();

	while(1)
	{
		ep = readdir(dp);

		// �����չ�
		if(ep == NULL)
			break;

		// �������������ļ�
		if(ep->d_name[0] == '.')
			continue;

                if(strstr(ep->d_name, ".mp3"))
                {
                        head = init_lianbiao(ep->d_name,head);
                }
               // printf("head->next->name2 = %s\n",head->next->name);
		// ��ȡ��ǰ�ļ���stat��Ϣ
		bzero(&info, sizeof(info));
		stat(ep->d_name, &info);

	//	printf("%s: %ld\n", ep->d_name, info.st_size);
	}

	// 3���ͷ���Ӧ����Դ
		//closedir(dp);

	return head;
}
