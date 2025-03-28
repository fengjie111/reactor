#include "Buffer.h"

Buffer::Buffer(uint16_t sep):sep_(sep)
{

}

Buffer::~Buffer()
{

}

// 把数据追加到buf_中。
void Buffer::append(const char *data,size_t size)             
{
    buf_.append(data,size);
}

// 把数据追加到buf_中，附加报文头部。
void Buffer::appendwithsep(const char *data,size_t size)  
{
    if(sep_==0){
        buf_.append(data,size);                    // 处理报文内容。
    }
    else if(sep_==1){
        buf_.append((char*)&size,4);           // 处理报文长度（头部）。
        buf_.append(data,size);                    // 处理报文内容。
    }
    else{
        buf_.append(data,size);                    // 处理报文内容。
        buf_.append("\r\n\r\n");
    }

}

// 从buf_的pos开始，删除nn个字节，pos从0开始。
void Buffer::erase(size_t pos,size_t nn)                             
{
    buf_.erase(pos,nn);
}

// 返回buf_的大小。
size_t Buffer::size()                                                            
{
    return buf_.size();
}

// 返回buf_的首地址。
const char *Buffer::data()                                                  
{
    return buf_.data();
}

// 清空buf_。
void Buffer::clear()                                                            
{
    buf_.clear();
}

bool Buffer::pickmessage(std::string& ss){              //从buf_中拆出一个报文，存放在ss中，如果buf_没有报文，返回false
    if(buf_.size()==0)return false;

    if(sep_==0){
        ss=buf_;
        buf_.clear();
    }
    else if(sep_==1){
        int len;
        memcpy(&len,buf_.data(),4);     // 从inputbuffer中获取报文头部。
        // 如果inputbuffer中的数据量小于报文头部，说明inputbuffer中的报文内容不完整。
        if (buf_.size()<len+4) return false;

        ss=buf_.substr(4,len);   // 从inputbuffer中获取一个报文。
        buf_.erase(0,len+4);                                 // 从inputbuffer中删除刚才已获取的报文。
    }
    else{
        size_t start_pos=buf_.find("\r\n\r\n");
        buf_.erase(start_pos,start_pos+4);
        ss=buf_;
        buf_.clear();
    }
    return true;
}