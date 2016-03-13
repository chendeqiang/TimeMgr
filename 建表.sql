create table things_set
(
keyid integer primary key autoincrement, --自增主键
start_time time,     --开始时间
end_time time,       --结束时间
do_things varchar(256),   --事项
priority varchar(256)  --优先级（象限）
);


create table object_plan
(
things varchar(4096)   --目标
);
insert into object_plan(things) values("");