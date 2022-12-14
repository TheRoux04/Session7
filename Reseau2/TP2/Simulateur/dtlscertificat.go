package main

import (
	"crypto/tls"
	"github.com/pion/dtls/v2"
)

type DtlsCertificat struct {
	certTls tls.Certificate
	cfgDtls *dtls.Config
}

func getDtlsCertificat() DtlsCertificat {
	cert, err := tls.LoadX509KeyPair("../localhost/cert.pem", "../localhost/key.pem")
	if err != nil {
		return DtlsCertificat{}
	}
	dtlsCfg := &dtls.Config{Certificates: []tls.Certificate{cert}}
	DtlsCertificat := DtlsCertificat{
		certTls: cert,
		cfgDtls: dtlsCfg,
	}
	return DtlsCertificat
}
