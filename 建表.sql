create table things_set
(
keyid integer primary key autoincrement, --��������
start_time time,     --��ʼʱ��
end_time time,       --����ʱ��
do_things varchar(256),   --����
priority varchar(256)  --���ȼ������ޣ�
);


create table object_plan
(
things varchar(4096)   --Ŀ��
);
insert into object_plan(things) values("");