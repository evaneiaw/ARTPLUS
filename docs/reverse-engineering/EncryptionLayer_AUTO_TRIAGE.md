# EncryptionLayer.dll — triagem automatica

- Gerado: 2026-11-19 02:53
- Caminho: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\EncryptionLayer.dll`
- Tamanho: 2639400 bytes
- SHA-256: `c6e229fa2cb709ee26011f90b4e5a12604054ce6d0811d4c4e1996c4445142b6`
- Arquitetura: x64
- DIE: PE64: Linker: Microsoft Linker(14.41.34435); Compiler: Microsoft Visual C/C++(19.41.34435)[C++]; Library: Microsoft C/C++ Runtime[dynamic]; Tool: Microsoft Visual Studio(2022, 17.11)
- Strings: 8771 capturadas; amostra em `rag/sources/EncryptionLayer.strings.txt`

## Secoes

| Secao | VA | VSize | RawSize | Entropia |
|---|---|---|---|---|
| .text | 0x1000 | 1655982 | 1656320 | 6.427 |
| .rdata | 0x196000 | 824982 | 825344 | 5.316 |
| .data | 0x260000 | 23296 | 13824 | 4.643 |
| .pdata | 0x266000 | 93696 | 93696 | 6.168 |
| .rsrc | 0x27D000 | 480 | 512 | 4.714 |
| .reloc | 0x27E000 | 37108 | 37376 | 5.434 |

## Strings de interesse (amostra)

- `An error occurred while encrypting/decrypting`
- `Decoding error`
- `Encoding error`
- `error while parsing %1`
- `error while parsing private key from %1`
- `error while parsing public key certificate from %1`
- `E:\Develop\1_sources\ArtProPlus_25.03.x\Depot\EncryptionLayer\Sources\GOpenSSLPKCS7Imp.cpp`
- `Verify error: %s`
- `document`
- `documentSeries`
- `documentIdentifier`
- `documentTitle`
- `documentVersion`
- `documentAuthor`
- `documentLocation`
- `documentPublisher`
- `setct-ErrorTBS`
- `id-on-xmppAddr`
- `XmppAddr`
- `id-aa-ets-SignaturePolicyDocument`
- `HTTP routines`
- `malloc failure`
- `internal error`
- `init fail`
- `operation fail`
- `nested asn1 error`
- `fetch failed`
- `error:%08lX:%s:%s:%s`
- `assertion failed: ctx->cipher->block_size == 1 || ctx->cipher->block_size == 8 || ctx->cipher->block_size == 16`
- `assertion failed: bl <= (int)sizeof(ctx->buf)`
- `assertion failed: b <= sizeof(ctx->buf)`
- `assertion failed: b <= sizeof(ctx->final)`
- `assertion failed: ctx->buf_len >= ctx->buf_off`
- `assertion failed: ctx->buf_off + i < (int)sizeof(ctx->buf)`
- `assertion failed: ctx->buf_off < (int)sizeof(ctx->buf)`
- `assertion failed: ctx->buf_len <= (int)sizeof(ctx->buf)`
- `assertion failed: i <= n`
- `assertion failed: ctx->buf_off <= (int)sizeof(ctx->buf)`
- `assertion failed: ctx->tmp_len <= 3`
- `assertion failed: j <= sizeof(c->iv)`
- `assertion failed: mdsize <= EVP_MAX_MD_SIZE`
- `assertion failed: embed == 0`
- `ERROR: selector [%d] invalid`
- `unspecified certificate verification error`
- `certificate signature failure`
- `CRL signature failure`
- `format error in certificate's notBefore field`
- `format error in certificate's notAfter field`
- `format error in CRL's lastUpdate field`
- `format error in CRL's nextUpdate field`
- `application verification failure`
- `CRL path validation error`
- `issuer certificate lookup error`
- `OCSP verification failed`
- `unknown certificate verification error`
- `assertion failed: (bit & 1) == 0`
- `assertion failed: list >= 0 && list < sh.freelist_size`
- `assertion failed: ((ptr - sh.arena) & ((sh.arena_size >> list) - 1)) == 0`
- `assertion failed: bit > 0 && bit < sh.bittable_size`
- `assertion failed: TESTBIT(table, bit)`
- `assertion failed: !TESTBIT(table, bit)`
- `assertion failed: WITHIN_FREELIST(list)`
- `assertion failed: WITHIN_ARENA(ptr)`
- `assertion failed: temp->next == NULL || WITHIN_ARENA(temp->next)`
- `assertion failed: (char **)temp->next->p_next == list`
- `assertion failed: WITHIN_FREELIST(temp2->p_next) || WITHIN_ARENA(temp2->p_next)`
- `assertion failed: !sh_testbit(temp, slist, sh.bitmalloc)`
- `assertion failed: temp != sh.freelist[slist]`
- `assertion failed: sh.freelist[slist] == temp`
- `assertion failed: temp-(sh.arena_size >> slist) == sh_find_my_buddy(temp, slist)`
- `assertion failed: sh_testbit(chunk, list, sh.bittable)`
- `assertion failed: WITHIN_ARENA(chunk)`
- `assertion failed: sh_testbit(ptr, list, sh.bittable)`
- `assertion failed: ptr == sh_find_my_buddy(buddy, list)`
- `assertion failed: ptr != NULL`
- `assertion failed: !sh_testbit(ptr, list, sh.bitmalloc)`
- `assertion failed: sh.freelist[list] == ptr`
- `%s:%d: OpenSSL internal error: %s`
- `assertion failed: ctx->length <= (int)sizeof(ctx->enc_data)`
- `Error in encoding`
- `Specifies to continue even if version checking fails (boolean)`
- `cryptacquirecontext error`
- `cryptenumproviders error`
- `decrypt error`
- `enumcontainers error`
- `error adding cert`
- `error creating store`
- `error getting friendly name`
- `error getting key provider info`
- `error opening store`
- `error signing hash`
- `file open error`
- `getuserkey error`
- `pubkey export error`
- `pubkey export length error`
- `win32 error`
- `debug level (1=errors, 2=trace)`
- `ERR_CAPI_error`
- `Error code= 0x`
- `othername: XmppAddr:`
- `othername:XmppAddr:%.*s`
- `assertion failed: nkey <= EVP_MAX_KEY_LENGTH`
- `assertion failed: niv <= EVP_MAX_IV_LENGTH`
- `%*s<Parse Error>`
- `assertion failed: keylen <= sizeof(key)`
- `KERNEL32.DLL`
- `assertion failed: l <= sizeof(iv)`
- `provider section error`
- `random section error`
- `secure malloc failure`
- `asn1 parse error`
- `asn1 sig parse error`
- `aux error`
- `decode error`
- `encode error`
- `error getting time`
- `error loading section`
- `error setting cipher params`
- `invalid separator`
- `list error`

## Lacunas

- funcoes/xrefs: aguardando export do Ghidra

