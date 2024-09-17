/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "nfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
nfs_program_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		char *ls_1_arg;
		char *create_1_arg;
		char *delete_1_arg;
		request retrieve_file_1_arg;
		chunk send_file_1_arg;
		char *mynfs_mkdir_1_arg;
		char *mynfs_open_1_arg;
		char *mynfs_close_1_arg;
		request mynfs_read_1_arg;
		chunk mynfs_write_1_arg;
		opendir_args mynfs_opendir_1_arg;
		readdir_args mynfs_readdir_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case ls:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_wrapstring;
		local = (char *(*)(char *, struct svc_req *)) ls_1_svc;
		break;

	case create:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) create_1_svc;
		break;

	case delete:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) delete_1_svc;
		break;

	case retrieve_file:
		_xdr_argument = (xdrproc_t) xdr_request;
		_xdr_result = (xdrproc_t) xdr_chunk;
		local = (char *(*)(char *, struct svc_req *)) retrieve_file_1_svc;
		break;

	case send_file:
		_xdr_argument = (xdrproc_t) xdr_chunk;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) send_file_1_svc;
		break;

	case mynfs_mkdir:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) mynfs_mkdir_1_svc;
		break;

	case mynfs_open:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) mynfs_open_1_svc;
		break;

	case mynfs_close:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) mynfs_close_1_svc;
		break;

	case mynfs_read:
		_xdr_argument = (xdrproc_t) xdr_request;
		_xdr_result = (xdrproc_t) xdr_chunk;
		local = (char *(*)(char *, struct svc_req *)) mynfs_read_1_svc;
		break;

	case mynfs_write:
		_xdr_argument = (xdrproc_t) xdr_chunk;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) mynfs_write_1_svc;
		break;

	case mynfs_opendir:
		_xdr_argument = (xdrproc_t) xdr_opendir_args;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) mynfs_opendir_1_svc;
		break;

	case mynfs_readdir:
		_xdr_argument = (xdrproc_t) xdr_readdir_args;
		_xdr_result = (xdrproc_t) xdr_readdir_result;
		local = (char *(*)(char *, struct svc_req *)) mynfs_readdir_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

// int
// main (int argc, char **argv)
// {
// 	register SVCXPRT *transp;

// 	pmap_unset (NFS_PROGRAM, NFS_VERSION_1);

// 	transp = svcudp_create(RPC_ANYSOCK);
// 	if (transp == NULL) {
// 		fprintf (stderr, "%s", "cannot create udp service.");
// 		exit(1);
// 	}
// 	if (!svc_register(transp, NFS_PROGRAM, NFS_VERSION_1, nfs_program_1, IPPROTO_UDP)) {
// 		fprintf (stderr, "%s", "unable to register (NFS_PROGRAM, NFS_VERSION_1, udp).");
// 		exit(1);
// 	}

// 	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
// 	if (transp == NULL) {
// 		fprintf (stderr, "%s", "cannot create tcp service.");
// 		exit(1);
// 	}
// 	if (!svc_register(transp, NFS_PROGRAM, NFS_VERSION_1, nfs_program_1, IPPROTO_TCP)) {
// 		fprintf (stderr, "%s", "unable to register (NFS_PROGRAM, NFS_VERSION_1, tcp).");
// 		exit(1);
// 	}

// 	svc_run ();
// 	fprintf (stderr, "%s", "svc_run returned");
// 	exit (1);
// 	/* NOTREACHED */
// }