

#include "loadUrl.h"

void test(unsigned char * data, int length, unsigned char * bigDataArray, int &dataResultLength)
{
    
    NSURL *end = [NSURL URLWithString:@"http://www.google.com.br/searchbyimage/upload"];
    
    //Request
    NSMutableURLRequest *req = [[NSMutableURLRequest alloc]initWithURL:end];
    
    //Foto
    NSData *fotoData =
    [NSData dataWithBytes:(const void *)data length:sizeof(unsigned char)*length];
    
    //; /// = UIImageJPEGRepresentation([UIImage imageNamed:@"palmilha.jpg"], 10.0f);
    NSLog(@"Tam em bytes: %d da imagem",[fotoData length]);
    
    //Boundary
    NSString *boundary = @"-----------------------";
    
    //Cabecalhos Data
    NSMutableData *dataBody = [NSMutableData data];
    //Seta o valor para o cabecalho Content-type
    [req setValue:[NSString stringWithFormat:@"multipart/form-data; boundary=%@",boundary] forHTTPHeaderField:@"Content-Type"];
    
    //Seta o método de envio como POST
    [req setHTTPMethod:@"POST"];
    
    //Seta um navegador ficticio
    [req setValue:@"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_4) AppleWebKit/537.4 (KHTML, like Gecko) Chrome/22.0.1229.94 Safari/537.4" forHTTPHeaderField:@"User-Agent"];
    [req setValue:@"text/plain" forHTTPHeaderField:@"Accept"];
    
    //Seta o corpo da requisição para enviar a imagem
    [dataBody appendData:[[NSString stringWithFormat:@"--%@\r\n",boundary] dataUsingEncoding:NSUTF8StringEncoding]];
    [dataBody appendData:[[NSString stringWithFormat:@"Content-Disposition: form-data; name=\"encoded_image\"; filename=\"upload.jpg\"\r\n"] dataUsingEncoding:NSUTF8StringEncoding]];
    [dataBody appendData:[[NSString stringWithFormat:@"Content-Type: image/jpg\r\n\r\n"] dataUsingEncoding:NSUTF8StringEncoding]];
    [dataBody appendData:fotoData];
    [dataBody appendData:[[NSString stringWithFormat:@"\r\n"] dataUsingEncoding:NSUTF8StringEncoding]];
    [dataBody appendData:[[NSString stringWithFormat:@"--%@--\r\n",boundary] dataUsingEncoding:NSUTF8StringEncoding]];
    [req setHTTPBody:dataBody];
    
    NSData *dataResposta = [NSURLConnection sendSynchronousRequest:req returningResponse:nil error:nil];
    
    NSLog(@"Tamanho em bytes da resposta: %d",[dataResposta length]);
    
    
    
    dataResultLength = [dataResposta length] / sizeof(unsigned char);
    memcpy(bigDataArray, [dataResposta bytes], dataResultLength);

}
