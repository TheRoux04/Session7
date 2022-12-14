package main

import (
	"crypto/tls"
)

type TlsCertificat struct {
	certTls tls.Certificate
	cfgTls  *tls.Config
}

func getCertificat() TlsCertificat {
	cert, err := tls.LoadX509KeyPair("../localhost/cert.pem", "../localhost/key.pem")
	if err != nil {
		return TlsCertificat{}
	}
	tlsCfg := &tls.Config{Certificates: []tls.Certificate{cert}}
	sslCertTCP := TlsCertificat{
		certTls: cert,
		cfgTls:  tlsCfg,
	}
	return sslCertTCP
}
