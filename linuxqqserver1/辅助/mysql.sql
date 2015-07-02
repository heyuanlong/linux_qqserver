create database qqserver;
use qqserver;

create table usermessage(
	qq char(10) not null unique,
	nickname varchar(10) not null,
	realname varchar(10) not null,
	age tinyint null,
	sex tinyint null);

create table user(
	qq char(10) not null unique,
	pass varchar(20) not null);

create table messagetable(
sender char(10) not null,
receiver char(10) not null,
mid bigint primary key,
classid varchar(5000) null,
messagetime timestamp not null default CURRENT_TIMESTAMP,
status tinyint not null);

create table friend(
me char(10) not null,
groupid smallint not null,
groupname char(10) not null,
you char(10) not null);


