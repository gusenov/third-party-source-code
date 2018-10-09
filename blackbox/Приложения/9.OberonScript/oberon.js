//(c) 2007 Ralph Sommerer. All rights reserved.
//V2.0beta July 6, 2007
String.prototype.trimBeg=function(){return this.replace(/^\s+/,"")}
String.prototype.startsWith=function(p){return(this.substr(0,p.length)==p)}
Array.prototype.last=function(){return this[this.length-1]}
//Scanner
function Scan(s){this.str=s.trimBeg()}
function find(i,o){for(var n in o){if(o[n]==i)return n}return "??("+i+")"}
Scan._kw={"ARRAY":1,"BEGIN":1,"BY":1,"CASE":1,"CONST":1,
    "DIV":1,"DO":1,"ELSE":1,"ELSIF":1,"END":1,"EXIT":1,"FOR":1,
    "IF":1,"IMPORT":1,"IN":1,"IS":1,"LOOP":1,"MOD":1,"MODULE":1,
    "OR":1,"OF":1,"POINTER":1,"PROCEDURE":1,"RECORD":1,"REPEAT":1,"RETURN":1,
    "THEN":1,"TO":1,"TYPE":1,"UNTIL":1,"VAR":1,"WHILE":1,"WITH":1};
Scan._jskw={"break":1,"case":1,"catch":1,"continue":1,"default":1,"delete":1,
  "do":1,"else":1,"false":1,"finally":1,"for":1,"function":1,  "if":1,"in":1,
  "instanceof":1,  "new":1,"null":1,"return":1,"switch":1,"this":1,
  "throw":1,"true":1,"try":1,"typeof":1,"var":1,"void":1,"while":1,"with":1,
  /*!!!*/"toString":-1};
//Scan._id={"NIL":1,"TRUE":1,"FALSE":1};
Scan._xid=/([a-zA-Z_]\w*)/;
Scan._xnum=/(\d+)/;
Scan._xnumx=/(\d[0-9A-F]*(X|H))/;
Scan._xnumr=/(\d+\.\d*((E|D)(\+|\-)?\d+)?)/;
Scan.init=function(i){var k=Scan._kw;for(var n in k)k[n]=i++}
Scan.KW=50;
Scan.init(Scan.KW);
Scan._kw["toString"]=-1;/*!!!*/
Scan.Err=-2;
Scan.EOS=-1;
Scan.Id=1;
Scan.Num=2;
Scan.Str=3;
Scan.ASSIGN=4;
Scan.LEQ=5;
Scan.GEQ=6;
Scan.LT=7;
Scan.GT=8;
Scan.EQ=9;
Scan.NEQ=10;
Scan.PLUS=11;
Scan.MINUS=12;
Scan.TIMES=13;
Scan.DIV=14;
Scan.AND=15;
Scan.PERIOD=16;
Scan.COLON=17;
Scan.OPAR=18;
Scan.CPAR=19;
Scan.OBRAK=20;
Scan.CBRAK=21;
Scan.OBRACE=22;
Scan.CBRACE=23;
Scan.SEMICOL=24;
Scan.COMMA=25;
Scan.TILDE=26;
Scan.BAR=27;
Scan.ELLIPSIS=28;
Scan.HAT=29;
//Scan._symE=":<>";
Scan._eqC=[Scan.ASSIGN,Scan.LEQ,Scan.GEQ];
Scan._neqC=[Scan.COLON,Scan.LT,Scan.GT];
Scan._sym="()[]{};,+-*/&=#^~|";
Scan._symC=[Scan.OPAR,Scan.CPAR,Scan.OBRAK,Scan.CBRAK,Scan.OBRACE,Scan.CBRACE,
  Scan.SEMICOL,Scan.COMMA,Scan.PLUS,Scan.MINUS,Scan.TIMES,Scan.DIV,Scan.AND,
  Scan.EQ,Scan.NEQ,Scan.HAT,Scan.TILDE,Scan.BAR];
Scan._sym0=["???","id","num","str","assign",
  "leq","geq","lt","gt","eq","neq",
  "plus","minus","times","div","and","period","colon",
  "opar","cpar","obrak","cbrak","obrace","cbrace","semicol","comma",
  "tilde","bar","ellips","hat"];
Scan._Sym=function(i){return (i<Scan.KW?Scan._sym0[i]+"("+i+")":find(i,Scan._kw))}
Scan.prototype.sym=function()
{
  var s=this.str;
  if(s.length==0)return Scan.EOS;
  if(s.search(Scan._xid)==0){
    var id=this.id=RegExp.$1;
    this.eat(id.length);
    var kw;
    if((kw=Scan._kw[id])>=Scan.KW)return kw;
    if(Scan._jskw[id]>0)this.id='_'+id;
    return Scan.Id;
  }else if(s.search(Scan._xnumr)==0){
    var num=RegExp.$1;
    var len=num.length;
    if(num.charAt(len-1)=='.'&&s.charAt(len)=='.'){
      this.num=parseInt(num.substr(0,len-1));
      this.eat(len-1);this.numtyp='intT'
    }else{
      this.eat(num.length);
      this.num=parseFloat(num)
    }
    this.numtyp='floatT'
    return Scan.Num;
  }else if(s.search(Scan._xnumx)==0||s.search(Scan._xnum)==0){
    var num=RegExp.$1;
    this.eat(num.length);
    var h=num.charAt(num.length-1);
    this.num=parseInt(num,(h=='X'||h=='H'?16:10));
    this.numtyp=(h=='X'||h=='H'?'hexT':'intT');//I,H,C
    return Scan.Num;
  }else{
    var x=s.charAt(0);
    if((i=":<>".indexOf(x))>=0){
      if(s.charAt(1)=='='){this.eat(2);return Scan._eqC[i]}
      this.eat(1);return Scan._neqC[i];
    }else if((i=Scan._sym.indexOf(x))>=0){
      if(i==0&&s.startsWith("(*")){
        this.eat(s.indexOf("*)")+2);return this.sym()
      }
      this.eat(1);return Scan._symC[i];
    }else if(x=='\''||x=='\"'){
      this.id=s.substring(1,s.indexOf(x,1));
      this.eat(this.id.length+2);
      return Scan.Str;
    }else if(x=='.'){
      if(s.charAt(1)=='.'){this.eat(2);return Scan.ELLIPSIS}
      this.eat(1);return Scan.PERIOD;
    }
    //else
    this.eat(1);
    return Scan.Err;
  }
}
Scan.prototype.eat=function(n){this.str=this.str.substr(n).trimBeg()}
//Parser
function Parse(cd)
{
  this.cd=cd;
  this.mods={};
}
Parse.prototype.compile=function(scn)
{
  this.scn=scn;
  this.cd.reset();
  this.lev=0;
  this.next();
  this.module()
}
Parse.prototype.next=function(){this.sym=this.scn.sym()/*;deb(" "+Scan._Sym(this.sym))*/}
Parse.prototype.error=function(m){if(!this.err){this.err=m}else{this.err+="<br>"+m}}
Parse.prototype.eat=function(sy){
  if(this.sym==sy)this.next();
  else this.error(Scan._Sym(sy)+" expected")
}
Parse.prototype.code=function(){return this.cd.toString()}
Parse.prototype.module=function()
{
  this.top=Parse.scope0;
  //module
  this.eat(Scan._kw.MODULE);
  this.ident();
  var md=this.mod=this.id;
  this.cd.put("function "+md+"(){");
  var m;
  this.push(m=new Obj('M',md));
  this.eat(Scan.SEMICOL);
  if(this.sym==Scan._kw.IMPORT){this.next();this.impList()}
  this._body(md,Scan.PERIOD);
  this.cd.put("}"+md+"();");
  this.addMod(m)
}
Parse.prototype.impList=function()
{
  this.imp();
  while(this.sym==Scan.COMMA){
   this.next();
   this.imp()
  }
  this.eat(Scan.SEMICOL)
}
Parse.prototype.imp=function()
{
  if(this.sym==Scan.Id){
    var m;
    this.ident();
    this.add(m=new Obj('M',this.id));
    if(this.sym==Scan.ASSIGN){
      this.next();
      this.ident();
      m.id0=this.id
    }
    var id=m.id0?m.id0:m.id;
    if(id=="HOST")m.dsc=[];
    else m.dsc=this.mods[id]?this.mods[id].dsc:null;
    //m.dsc=(id!="HOST"?this.mods[id].dsc:[]);//error
    if(!m.dsc)this.error("no such module ("+id+")")
  }else{
    this.error("id expected")
  }
}
Parse.prototype._body=function(n,sy)
{
  this.declSeq();
  //this.dump();
  if(this.sym==Scan._kw.BEGIN){this.next();this.stmtSeq()}
  this.eat(Scan._kw.END);
  if(this.sym==Scan.Id&&this.scn.id==n){this.next();this.eat(sy)}
  else this.error("id "+n+" expected")
}
Parse.prototype.stmtSeq=function()
{
  this.stmt();
  while(this.sym==Scan.SEMICOL){this.next();this.cd.put(";");this.stmt()}
}
Parse.prototype.ident=function(md)
{
  var n=null;
  if(this.sym==Scan.Id){
    this.id=this.scn.id;
    if(md)this.add(n=new Obj(md,this.id));
    this.next();
  }else{
    this.error("id expected ("+Scan._Sym(this.sym)+")");
    if(md)n=new Obj(md,"??")
  }
  return n
}
Parse.prototype.qualid=function()
{
  var m=null;
  this.ident();
  //debB('#fc0',this.id);
  if(this.sym==Scan.PERIOD&&(m=this.find(this.id))&&m.md=='M'){
    //m=this.find(this.id);
    this.next();
    this.ident()
    return m
  }
  //debB('#f42',"no");
  return null
}
Parse.prototype.identDef=function(md)
{
  this.mk=null;
  this.ident(md);
  if(this.sym==Scan.TIMES){
    this.next();
    this.mk=(this.lev==1?this.mod:null);
    if(md)this.top.dsc.last().mk=this.mk;
    //export
    if(!this.mk)this.error("export error")
  }
}
Parse.prototype.type=function()
{
  var t=null,m;
  var sy=this.sym;
  if(sy==Scan.Id){
    m=this.qualid();
    t=this.findT(this.id,m);
    //debB('#0ff',dumpT(t));
    //debB('#ff8',this.id);
    if(!t&&m&&m.id=="HOST")m.dsc.push(t=new Obj('T',this.id,"HOST"));
    if(!t){this.error("no such type ("+this.id+")");t=Obj.noT}
  }else{
    this.next();
    if(sy==Scan._kw.ARRAY){
      t=new Obj('A');
      t.dim=[];
      this.exprList(t.dim);
      this.eat(Scan._kw.OF);
      t.typ=this.type()
    }else if(sy==Scan._kw.RECORD){
      this.push(t=new Obj('R'));
      if(this.sym==Scan.OPAR){
        this.next();
        m=this.qualid();
        t.typ=this.findT(this.id,m);
        if(!t.typ)this.error("no such type ("+(m?m.id+'.':"")+this.id+")");
        this.eat(Scan.CPAR)
      }
      this.fldList();
      while(this.sym==Scan.SEMICOL){
        this.next();
        this.fldList()
      }
      this.pop();
      this.eat(Scan._kw.END)
    }else if(sy==Scan._kw.POINTER){
      t=new Obj('^');
      this.eat(Scan._kw.TO);
      if(this.sym==Scan.Id){
        m=this.qualid();
        t.typ=this.findT(this.id,m);
        if(!t.typ){
          this.add(t.typ=new Obj('?',this.id))
        }
      }else{
        t.typ=this.type()
      }
    }else if(sy==Scan._kw.PROCEDURE){
      t=this.procTyp()
    }
  }
  return t
}
Parse.prototype.procTyp=function()
{
  //this.eat(Scan._kw.PROCEDURE);
  var p=new Obj('X');
  this.push(p);
  if(this.sym==Scan.OPAR)this.fmPars();
  this.pop();
  return p
}
Parse.prototype.fldList=function()
{
  if(this.sym==Scan.Id){
    var i=this.mark();
    this.idList();
    this.eat(Scan.COLON);
    this.setT(i,this.type())
  }
}
Parse.prototype.declSeq=function()
{
  this.lev++;
  while(true){
    var sy=this.sym;
    if(sy==Scan._kw.CONST){
      this.next();
      this.constDecl();
    }else if(sy==Scan._kw.TYPE){
      this.next();
      this.typDecl();
    }else if(sy==Scan._kw.VAR){
      this.next();
      this.varDecl();
    }else{
      break;
    }
  }
  while(this.sym==Scan._kw.PROCEDURE){this.next();this.procDecl()}
  this.lev--
}
Parse.prototype.constDecl=function()
{
  var c;
  while(this.sym==Scan.Id){
    this.identDef();//'C'
    this.add(c=new Obj('C',this.id,this.mk));
    this.eat(Scan.EQ);
    c.v=this.expr();
    this.cd.putI(c.id_("var")+"=",c.v,";");
    this.eat(Scan.SEMICOL)
  }
}
Parse.prototype.typDecl=function()
{
  var t;
  while(this.sym==Scan.Id){
    this.identDef();
    t=this.find(this.id);
    if(!t||t.md!='?')this.add(t=new Obj('T',this.id,this.mk));
    else{t.md='T';t.mk=this.mk}
    this.eat(Scan.EQ);
    t.typ=this.type();
    //debB('#f8f',":"+dumpT(t)+":"+t.md);
    var f=t.frm();
    if(f&&f.md=='^'&&f.typ.md=='?'){
      f=f.typ;
      if(!f.alias)f.alias=[];
      f.alias.push(t)
    }
    //debB('#ff0',dumpT(t));debLn();
    this.cd.putT(t);
    this.eat(Scan.SEMICOL)
  }
}
Parse.prototype.varDecl=function()
{
  while(this.sym==Scan.Id){
    var i=this.mark();
    this.idList();
    this.eat(Scan.COLON);
    this.setT(i,this.type());
    this.cd.vars(this.top.dsc,i);
    this.eat(Scan.SEMICOL)
  }
}
Parse.prototype.list=function(d)
{
  var s="";for(var i=0;i<d.length;++i)s+=","+d[i].id;
  return s.substr(1)
}
Parse.prototype.procDecl=function()
{
  var r=null,c=this.cd;
  if(this.sym==Scan.OPAR){
    /*O2:PROC(VAR r:R)P*()-->M.R.prototype.P=fun(){var r=this;*/
    this.next();
    if(this.sym==Scan._kw.VAR)this.next();
    this.ident();r=new Obj('V',this.id);
    this.eat(Scan.COLON);
    this.ident();r.typ=this.findT(this.id);
    this.eat(Scan.CPAR)
  }
  this.identDef();
  var pc;
  this.push(this.add(pc=new Obj('P',this.id,this.mk)));
  c.put(c.fn(pc,r)+"(");
  if(this.sym==Scan.OPAR){
    this.fmPars();
  }
  this.eat(Scan.SEMICOL);
  c.put(this.list(pc.dsc));
  c.put("){");
  this.push(new Obj('l'));//locals
  if(r){c.put("var "+r.id+"=this;");this.add(r)}
  this.declSeq();
  this._body(pc.id,Scan.SEMICOL);
  c.put("};");
  this.pop();
  this.pop()
}
Parse.prototype.fmPars=function()
{
  this.eat(Scan.OPAR);
  if(this.sym!=Scan.CPAR){
    this.fpSec();
    while(this.sym==Scan.SEMICOL){
      this.next();
      this.fpSec()
    }
  }
  this.eat(Scan.CPAR);
  if(this.sym==Scan.COLON){
    this.next();
    var m=this.qualid();
    this.top.typ=this.findT(this.id,m)
  }else{
  //  this.top.typ=Obj.noT
  }
}
Parse.prototype.fpSec=function()
{
  var v='V';
  if(this.sym==Scan._kw.VAR){
    this.next();
    v='W'//varpar
  }
  var i=this.mark();
  this.ident(v);
  while(this.sym==Scan.COMMA){
    this.next();
    this.ident(v);
  }
  this.eat(Scan.COLON);
  this.setT(i,this.fmType())
}
Parse.prototype.fmType=function()
{
  var t0=null,ta,t;
  while(this.sym==Scan._kw.ARRAY){
    if(!t0){t0=ta=new Obj('A')}else{t0.typ=new Obj('A');t0=t0.typ}
    this.next();
    this.eat(Scan._kw.OF)
  }
  if(this.sym==Scan._kw.PROCEDURE){
    this.next();
    t=this.procTyp()
  }else{
    var m=this.qualid();
    t=this.findT(this.id,m)
  }
  if(t0){t0.typ=t;t=ta}
  return t
}
Parse.prototype.idList=function()
{
  this.identDef('V');//ident();
  while(this.sym==Scan.COMMA){
    this.next();
    this.identDef('V')
  }
}
Parse.prototype.stmt=function()
{
  var e;
  var c=this.cd;
  if(this.sym==Scan._kw.IF){
    this.next();
    e=this.expr();
    this.eat(Scan._kw.THEN);
    c.putI("if(",e,"){");
    this.stmtSeq();
    while(this.sym==Scan._kw.ELSIF){
      this.next();
      e=this.expr();
      this.eat(Scan._kw.THEN);
      c.putI("}else if(",e,"){");
      this.stmtSeq()
    }
    if(this.sym==Scan._kw.ELSE){this.next();c.put("}else{");this.stmtSeq()}
    this.eat(Scan._kw.END);
    c.put("}")
  }else if(this.sym==Scan._kw.CASE){
    this.next();
    e=this.expr();
    this.eat(Scan._kw.OF);
    c.putI("switch(",e,"){");
    this.case_()
    while(this.sym==Scan.BAR){
      this.next();this.case_()
    }
    if(this.sym==Scan._kw.ELSE){this.next();c.put("default:");this.stmtSeq()}
    this.eat(Scan._kw.END);
    c.put("}")
  }else if(this.sym==Scan._kw.WHILE){
    this.next();
    e=this.expr();
    this.eat(Scan._kw.DO);
    c.putI("while(",e,"){");
    this.stmtSeq();
    this.eat(Scan._kw.END);
    c.put("}")
  }else if(this.sym==Scan._kw.REPEAT){
    c.put("do{");
    this.next();
    this.stmtSeq();
    this.eat(Scan._kw.UNTIL);
    e=this.expr();
    c.putI("}while(!(",e,"));")
  }else if(this.sym==Scan._kw.FOR){
    /*O2*/
    var e0,e1,e2=null;
    this.next();
    this.ident();
    var n=this.find(this.id);
    if(!n)this.error(this.id+" not found");
    this.eat(Scan.ASSIGN);
    var e0=this.expr();
    this.eat(Scan._kw.TO);
    var e1=this.expr();
    if(this.sym==Scan._kw.BY){
      this.next()
      e2=this.expr();//const
      if(e2.md!='C')this.error("for inc not const ("+e2.md+")");
    }
    this.eat(Scan._kw.DO);
    c.putFor(n,e0,e1,e2);
    this.stmtSeq();
    this.eat(Scan._kw.END);
    c.put("}")
  }else if(this.sym==Scan._kw.LOOP){
    c.put("while(true){");
    this.next();
    this.stmtSeq();
    this.eat(Scan._kw.END);
    c.put("}")
  }else if(this.sym==Scan._kw.WITH){
    this.next();
    this.guard();
    this.eat(Scan._kw.DO);
    this.stmtSeq();
    while(this.sym==Scan.BAR)/*O2*/
    {
      this.next();
      this.eat(Scan._kw.DO);
      this.stmtSeq()
    }
    if(this.sym==Scan._kw.ELSE){this.next();this.stmtSeq()}/*O2*/
    this.eat(Scan._kw.END)
  }else if(this.sym==Scan._kw.EXIT){
    this.next();
    c.put("break")
  }else if(this.sym==Scan._kw.RETURN){
    this.next();
    c.put("return");
    if(this.sym!=Scan.SEMICOL&&this.sym!=Scan.BAR&&this.sym<Scan.KW){
      e=this.expr();
      c.putI("(",e,")")
    } 
  }else if(this.sym==Scan.Id){
    e=this.desig();
    if(this.sym==Scan.ASSIGN){
      this.next();
      //e.op2(Scan.ASSIGN,e,this.expr());
      e.assign(e,this.expr());
      c.put(e)
    }else{
      this.call(e);
      c.put(e)
    }
  }
}
Parse.prototype.guard=function()
{
  this.qualid();
  this.eat(Scan.COLON);
  this.qualid()
}
Parse.prototype.call=function(e)
{
  var el=[];
  if(this.sym==Scan.OPAR){
    this.next();
    if(this.sym!=Scan.CPAR)this.exprList(el);
    this.eat(Scan.CPAR)
  }
  e.call(this.findQ(e),e,el,this)
}
Parse.prototype.deref=function(o,n)
{
  if(!o){/*debB('#f44',"null");*/return null;}
//debB('#fc8'," T:"+o.id_()+":"+dumpT(o));
  var f=o.frm(),d;
  if(!f&&o.mk=="HOST")return new Obj('H',n,"HOST");
  if(f.md=='^')return this.deref(f.typ,n);
//if(f.typ)debB('#c8f'," T:"+f.typ.id_()+":"+dumpT(f.typ));
  if(f.md=='R')return((d=f.find(n))?d:this.deref(f.typ,n));
  this.error("no record ("+o.id+")");
  return null
}
Parse.prototype.desig=function()
{
  var m=this.qualid();
  var id=this.id;
  var n=this.find(id,m);
  if(!n&&m&&m.id=="HOST"){m.dsc.push(n=new Obj('H',id,"HOST"));n.typ=Obj.hostT}
  //debB('#4f2',' '+id+'='+(n?n.id+":"+n.md+":"+(n.typ?n.typ.id:"??"):'??'));
  var e=(n?new Itm(n.id_(),n.typ,n.md):new Itm(id,Obj.noT,'V'));
  while(true){
    if(this.sym==Scan.PERIOD){
      this.next();
      this.ident();
      n=this.deref(e.typ,this.id);
      if(!n){this.error("no such field ("+this.id+")");n={'typ':Obj.noT,'id':'??'}}
      //new Itm(n.id,n.typ,'V')
      e.op2(Scan.PERIOD,e,new Itm(n.id,n.typ,n.md));
      e.typ=n.typ;e.md=n.md;
      e.dz=n.id
    }else if(this.sym==Scan.OBRAK){
      this.next();
      var f=e.typ.frm();
      if(f.md!='A')this.error("no array");
      //new Itm("",f.typ,'V');
      var el=[];
      this.exprList(el);
      e.arr(e,el,n.typ);
      e.md='V';
      e.az=""+el.last();
      this.eat(Scan.CBRAK)
    }else if(this.sym==Scan.HAT){
      this.next()
      e.typ=e.typ.typ;e.mod='V'
    }else if(this.sym==Scan.OPAR&&n&&n.typ&&(n.md=='V'||n.md=='W')&&(n.typ.md!='X')){
      this.next();
      m=this.qualid();
      e.typ=this.findT(this.id,m);
      if(!e.typ){this.error("no such type ("+this.id+")");e.typ=Obj.noT}
      //e.chk(e,n.typ)
      this.eat(Scan.CPAR)
    }else{
      break;
    }
  }
  return e
}
Parse.prototype.exprList=function(a)
{
  a.push(this.expr());
  while(this.sym==Scan.COMMA){
    this.next();
    a.push(this.expr())
  }
}
Parse.prototype.expr=function()
{
  var e=this.simExpr();
  while(this.sym>=Scan.LEQ&&this.sym<=Scan.NEQ||this.sym==Scan._kw.IN||this.sym==Scan._kw.IS){
    var op=this.sym;
    this.next();
    e.op2(op,e,this.simExpr())
  }
  return e;
}
Parse.prototype.simExpr=function()
{
  var neg=false;
  if(this.sym==Scan.PLUS||this.sym==Scan.MINUS){neg=(this.sym==Scan.MINUS);this.next()}
  var e=this.term();
  if(neg)e.op(Scan.MINUS,e);
  while(this.sym==Scan.PLUS||this.sym==Scan.MINUS||this.sym==Scan._kw.OR){
    var op=this.sym;
    this.next();
    e.op2(op,e,this.term())
  }
  return e
}
Parse.prototype.term=function()
{
  var e=this.factor();
  while(this.sym>=Scan.TIMES&&this.sym<=Scan.AND||this.sym==Scan._kw.DIV||this.sym==Scan._kw.MOD){
    var op=this.sym;
    this.next();
    e.op2(op,e,this.factor())
  }
  return e
}
Parse._defId={"NIL":"null","TRUE":"true","FALSE":"false"};
Parse.prototype.factor=function()
{
  var e;
  if(this.sym==Scan.Id){
    var d=Parse._defId[this.scn.id];
    if(d){e=new Itm(d,(d=="null"?Obj.noT:Obj.boolT),'C');this.next()}
    else e=this.desig();
    if(this.sym==Scan.OPAR)this.call(e);
  }else if(this.sym==Scan.Num){
    e=new Itm(this.scn.num,Obj[this.scn.numtyp],'C');
    this.next()
  }else if(this.sym==Scan.Str){
    e=new Itm("\""+this.scn.id.replace(/\\/g,"\\\\")+"\"",Obj.strT,'C');
    this.next()
  }else if(this.sym==Scan.OBRACE){
    e=this.set_()
  }else if(this.sym==Scan.OPAR){
    this.next();
    e=this.expr();
    e.op(Scan.OPAR,e);
    this.eat(Scan.CPAR)
  }else if(this.sym==Scan.TILDE){
    this.next();
    e=this.factor();
    e.op(Scan.TILDE,e)
  }
  return e
}
Parse.prototype.range=function(fn)
{
  var e=this.expr(),e0=null;
  if(this.sym==Scan.ELLIPSIS){
    this.next();
    e0=this.expr();
  }
  if(fn)fn(e,e0)
  return e
}
function rcase(e,f){
  var i=e.v;
  e.v="case "+(i++)+":";
  if(f){
    while(i<=f.v){e.v+="case "+(i++)+":"}
  }
}
Parse.prototype.case_=function()
{
  if(this.sym!=Scan.BAR&&this.sym!=Scan.ELSE&&this.sym!=Scan.END){
    var c=this.cd;
    var e=this.range(rcase);
    c.put(e);
    while(this.sym==Scan.COMMA){
      this.next();
      e=this.range(rcase);
      c.put(e);
    }
    this.eat(Scan.COLON);
    this.stmtSeq();
    this.cd.put(";break;")
  }
}
function rset(e,f){e.setop(e,f)}
Parse.prototype.set_=function()
{
  var e;
  this.eat(Scan.OBRACE);
  if(this.sym!=Scan.CBRACE){
    e=this.range(rset);
    while(this.sym==Scan.COMMA){
      this.next();
      var e0=this.range(rset);
      e.op2(Scan.PLUS,e,e0)
    }
  }else{
    e=new Itm(0,Obj.setT,'C')
  }
  this.eat(Scan.CBRACE);
  return e
}
//Scope
Parse.prototype.push=function(o)
{
  o.down=this.top;this.top=o
}
Parse.prototype.pop=function()
{
  var o=this.top;
  this.top=o.down;
  delete o.down;
  return o
}
Parse.prototype.addMod=function(m)
{
  var d=m.dsc;
  m.dsc=[];
  for(var i=0;i<d.length;++i){
    if(d[i].mk)m.dsc.push(d[i])
  }
  this.mods[m.id]=m
}
function dumpT(t)
{
  if(t)return("["+(t.id?t.id_():"_")+(t.mk?'*':"")+":"+t.md+dumpT(t.typ)+"]");
  return ""
}
function dumpD(o,t)
{
  var s="";
  for(var i=0;i<o.dsc.length;++i){
    var p=o.dsc[i];
    s+=("&nbsp;"+p.id+":"+p.md);
    if(p.md=='P')s+="("+dumpD(p,false)+")";
    if(p.md=='V'&&p.typ&&p.typ.md=='X')s+="("+dumpD(p.typ,false)+")";
    if(p.md=='R')s+="{"+dumpD(p,false)+"}";
    if(t&&p.typ)s+=(dumpT(p.typ))
  }
  return s
}
Parse.prototype.dump=function()
{
  var s="<br>";
  var o=this.top;
  while(o){s+=(o.id+":"+o.md);
    s+=dumpD(o,true);
    s+="<br>";
    o=o.down
  }
  debLn("<br>====="+s);
}
Parse.prototype.findQ=function(n)
{
  var s=n.toString(),i=s.indexOf('.');
  if(i>0)return this.find(s.substr(i+1),this.find(s.substr(0,i)));
  return this.find(s)
}
Parse.prototype.find=function(n,m)
{
  var c=(m?m:this.top);
  while(c){
    for(var i=0;i<c.dsc.length;++i){
      if(c.dsc[i].id==n)return c.dsc[i]
    }
    c=c.down
  }
  return null
}
Parse.prototype.findT=function(n,m)
{
  var t=this.find(n,m);return(t&&t.md=='T'?t:null)
}
Parse.prototype.add=function(o)
{
  this.top.dsc.push(o);return o
}
Parse.prototype.mark=function()
{
  return this.top.dsc.length;
}
Parse.prototype.setT=function(i,t)
{
//if(!t)debB('#f00',"No type!!!");
  var d=this.top.dsc;
  while(i<d.length)d[i++].typ=t
}
//
function addObj(d,md,ids,t)
{
  var o=null;
  for(var i=0;i<ids.length;++i){
    d.push(o=new Obj(md,ids[i]));o.typ=t
  }
}
//Obj
function Obj(md,id,mk)
{
  this.md=md;
  this.id=(id?id:'_');
  this.mk=mk;
  this.typ=null;
  this.dsc=[]
}
Obj.prototype.find=function(n)
{
  var d=this.dsc;
  for(var i=0;i<d.length;++i){
    if(d[i].id==n)return d[i]
  }
  return null
}
Obj.prototype.frm=function()
{
  var t=this;
  while(t&&t.id!='_'){/*debB("#8fc",t.id+":"+t.md+' ');*/t=t.typ};
  return t
}
Obj.prototype.init=function()
{
  var t=this;
  var f=t.frm();
  if(!f)return "null";
  if(f.md=='B')return(f==Obj.boolT?"false":"0");
  else if (f.md=='R')return "new "+t.id_()+"()"
  else if (f.md=='A'){
    var ff=f.typ.frm(),z;
    if(Obj.isNumT(ff))z="_narr(0,";
    else if(ff==Obj.boolT)z="_narr(false,";
    else z="_arr(function(){return "+f.typ.init()+"},"
    return z+t.dim.join()+")"
  }
  return "null"
}
Obj.prototype.id_=function(p)
{
  return (this.mk&&this.mk!="HOST"?this.mk+"."+this.id:(p?p+' ':"")+this.id)
}
Obj.noT=new Obj('T',"??");
Obj.hostT=new Obj('T',"??","HOST");

Obj.intT=Obj.hexT=new Obj('B');//"int"
Obj.boolT=new Obj('B');//"bool"
Obj.floatT=new Obj('B');//"float"
Obj.setT=new Obj('B');//"set"
Obj.strT=new Obj("string");//"string"
Obj.isNumT=function(t){return t==Obj.intT||t==Obj.floatT||t==Obj.setT}

Parse.scope0=new Obj('0',"_");
addObj(Parse.scope0.dsc,'T',["INTEGER","SHORTINT","LONGINT","CHAR"],Obj.intT),
addObj(Parse.scope0.dsc,'T',["REAL","LONGREAL"],Obj.floatT);
addObj(Parse.scope0.dsc,'T',["BOOLEAN"],Obj.boolT);
addObj(Parse.scope0.dsc,'T',["SET"],Obj.setT);
//Item
function Itm(v,t,m)
{
  this.v=v;//val
  this.typ=t;
  this.md=m
}
Itm.prototype.toString=function()
{
  if(this.md=='W'){var f=this.typ.frm();if(f.md!='R'&&f.md!='A')return this.v+"()"}
  return this.v
}
Itm.prototype.op=function(op,x)
{
  if(x.md=='C'){
    if(op==Scan.MINUS){
      this.v=(x.typ==Obj.setT?~x.v:-x.v)
    }else if(op==Scan.OPAR){
      this.v=x.v
    }else if(op==Scan.TILDE){
      this.v=!x.v
    }
    this.md='C'
  }else{
    if(op==Scan.MINUS){
      this.v=(x.typ==Obj.setT?"~":"-")+x.v
    }else if(op==Scan.OPAR){
      this.v="("+x.v+")"
    }else if(op==Scan.TILDE){
      this.v="!"+x.v
    }
    this.md='V'
  }
  this.typ=x.typ
}
Itm.rel=['=','<=','>=','<','>','==','!='];
Itm.num=['+','-','*','/','&&','.'];
Itm.bin=['|','&~','&','^','&&','.'];
Itm.prototype.op2=function(op,x,y)
{
  var s;
  if(op<Scan.KW){
    if(op<=Scan.NEQ)s=Itm.rel[op-Scan.ASSIGN];
    else{
      if(x.typ==Obj.setT){
        s=Itm.bin[op-Scan.PLUS];
        if(op==Scan.MINUS)x.op(Scan.OPAR,x)
      }else{
        s=Itm.num[op-Scan.PLUS];
      }
    }
  }else if(op==Scan._kw.OR){
    s='||'
  }else if(op==Scan._kw.DIV||op==Scan._kw.MOD){
    this.v='Math.floor('+x+(op==Scan._kw.DIV?'/':'%')+y+')';this.md='V';return
  }else if(op==Scan._kw.IS){
    s=' instanceof '
  }
  this.v=x+s+y;
  this.md='V'
}
Itm.prototype.assign=function(x,y)
{
  var md=x.md;
  this.md='V';this.typ=x.typ;/*!!*/
  //debB('#ff0',"ass:"+x.v+":"+x.md+";");
  if(md=='W'){
    var f=x.typ.frm();
    if(f.md!='R'&&f.md!='A'){this.v=x.v+"("+y+")";return}
  }
  this.op2(Scan.ASSIGN,x,y)
}
Itm.prototype.arr=function(x,a,t)
{
  this.v=x+"["+a.join("][")+"]";
  this.typ=t;
  this.md='V'
}
Itm.prototype.call=function(n,x,a,prs)
{
  //debB('#f80'," "+x+(n?":"+n.id:":-"));
  if(JS.stdFn(this,x,a))return;
  var dsc;
  if(x.md=='H'){/*deb("HOST");*/dsc=null;}
  else{
    if(n&&n.md=='V')n=n.typ.frm();
    dsc=(n?n.dsc:x.typ.dsc);
    if(dsc.length!=a.length){prs.error("arg mismatch");return}
  }
  
  var a0=[];
  for(var i=0;i<a.length;++i)a0.push(this.arg(a[i],dsc?dsc[i]:null));
  this.v=x+"("+a0.join()+")";
  this.typ=x.typ;
  this.md='V'
}
Itm.prototype.setop=function(x,y)
{
  if(y){
    if(x.md=='C'&&y.md=='C'){this.v=(-1<<x.v)&~(-2<<y.v);this.md='C'}
    else this.v="("+(x.md=='C'?(-1<<x.v):"-1<<("+x+")")+"&~"+(y.md=='C'?(-2<<y.v):"((-2)<<("+y+"))")+")";this.md='V'
  }else{
    this.v=(x.md=='C'?(1<<x.v):"(1<<("+x+"))");
    this.md=x.md
  }
  this.typ=Obj.setT
}
//a[]..[x][y]->a[]..[x],y
//p...q.r-> p...q,"r"
function undesig(d,z,dot)
{
  return d.substr(0,d.length-z.length-(dot?1:2))+","+(dot?'\"'+z+'\"':z)
}
/*
function undesig(d,z,n){return [d.substr(0,z.length-n),z]}
*/
Itm.prototype.arg=function(a,p)//a:Itm=arg,p:Itm=formal par
{
  if(p){
  //debB('#0cf',p.id+":"+dumpT(p.typ));
  var f=(p.typ?p.typ.frm():Obj.noT);
  if(!f)f=Obj.noT;
  if(p.md=='W'){
    if(a.dz||a.az)return "_vp("+undesig(a.v,a.dz?a.dz:a.az,a.dz)+")"
    else if(f.md!='R'&&f.md!='A'&&a.md!='W')return "function($){return $?"+a.v+"=$:"+a.v+"}";
  }else{//V
    if(f.md=='R')return p.typ.init()+"._cp("+a.v+")";
    else if(f.md=='A')return "_cpa("+p.typ.init()+","+a.v+")";
    else if(a.md=='W')return a.v+"()";
  }
  }else{
  //debB('#f63',"p is null");
  }
  return a.v
}
//code
function JS(){this.c=""}
JS.prototype.reset=function(){this.c=""}
JS.prototype.toString=function(){return this.c}
JS.prototype.put=function(c){this.c+=c}
JS.prototype.fn=function(o,r)
{
  if(r)return r.typ.id_()+".prototype."+o.id+"=function";
  return (o.mk?o.mk+"."+o.id+"=function":"function "+o.id)
}
JS.prototype.ext=function(t,b)
{
  var s="",f=t.frm();
  for(var i=0;i<f.dsc.length;++i){
    var d=f.dsc[i],g=d.typ.frm();
    s+=","+(g.md=='R'?'#':(g.md=='A'?""+g.dim.length:""))+d.id
  }
  return "_ext("+t.id_()+(b?","+b.id_():"")+",\""+s.substr(1)+"\");"
}
JS.prototype.putT=function(t)
{
  if(t.typ&&t.typ.md=='T'){
    this.c+=t.id_("var")+"="+t.typ.id_()+";"
  }else{
    var f=t.frm();
    //base call unnecessary: if(f.md=='R')this.c+=this.fn(t)+"(){"+(f.typ?f.typ.id+".call(this);":"")+this.flds(f)+"}";
    if(f.md=='R'){
      this.c+=this.fn(t)+"(){"+this.flds(f)+"};"+(true||f.typ?this.ext(t,f.typ):"");
      if(t.alias)for(var i=0;i<t.alias.length;++i)this.c+=t.alias[i].id_()+"="+t.id_()+";";
    }
  }
}
JS.prototype.flds=function(o)
{
  var d=o.dsc,s="";
  for(var i=0;i<d.length;++i)s+=";this."+d[i].id+"="+d[i].typ.init();//t.typ.frm().init()
  return s.substr(1)
}
JS.prototype.putI=function(p,e,s)
{
  this.c+=p+e+s
}
JS.prototype.vars=function(d,i0)
{
  if(i0<d.length){
    var s="",m="";
    while(i0<d.length){
      var di=d[i0++];
      if(!di.typ)continue;
      var f=di.typ.frm();
      if(di.mk)m+=di.id_()+"="+di.typ.init()+";"
      else s+=","+di.id+(f&&(f.md=='R'||f.md=='A')?"="+di.typ.init():"")
    }
    this.c+=(s.length>0?"var "+s.substr(1)+";":"")+m
  }
}
/*
function scalar(t)
{
  t=t.frm();return(t.md!='R'&&t.md!='A')
}
JS.assign=function(e,f,arg)
{
  if(e.md=='V'&&f.md=='V'){
    if(scalar(e.typ))this.c+=e+"="+f;
    else this.c+="_cpy("+e+","+f+")"
  }else if(e.md=='W'){
    if(f.md=='W')this.c+=e+"="+f;
  }
}
*/
JS.prototype.putFor=function(n,e0,e1,e2)
{
  var v=n.id_();
  var s="for("+v+"="+e0+";";
  var b=(!e2?1:e2.v);
  if(b>0)s+=v+"<="+e1+";"+v+(b>1?"+="+b:"++");
  else s+=v+">="+e1+";"+v+(b<1?"-="+b:"--");
  this.c+=s+"){"
}
//MIN(T) MAX(t) SIYE(T) ODD ORD CAP CHR LEN SHORT LONG ABS ENTIER
//INC DEC INCL EXCL NEW ASH
//STRING CHRARR
JS.updV=function(op,a0,a1)
{
  return a0.v+"("+a0.v+"()"+op+a1+")"
}
JS._fnx={"ABS":"Math.abs(#)","CAP":"((#)&0x5f)","CHR":"((#)&0xff)",
  "ENTIER":"Math.floor(#)","LONG":"(#)","ODD":"((#)&1)","ORD":"(#)",
  "SHORT":"((#)&0xffff)","STRING":"(#).join('')","CHRARR":"_charr(#)"
};
JS.stdFn=function(e,x,a)
{
  var id=x.v,s,op=null;
  var a0=a[0],a1=(a.length>1?a[1]:null);
  switch(id){
  case "NEW":
    e.assign(a[0],new Itm("new "+a[0].typ.id_()+"()"));
    break;
  case "ASH":
    e.v="("+a0+"<<"+(a1?"("+a1+")":"1")+")";
    break;
  case "INC":
    if(a0.md=='V')e.v=a0+(a1?"+="+a1:"++");
    else e.v=JS.updV('+',a0,(a1?a1:"1"));
    //e.v=a0.v+"("+a0.v+"()+"+(a1?a1:"1")+")";break;
    break;
  case "DEC":
    if(a0.md=='V')e.v=a0+(a1?"-="+a1:"--");
    else e.v=JS.updV('+',a0,(a1?a1:"1"));
    //else e.v=a0.v+"("+a0.v+"()-"+(a1?a1:"1")+")";break;
    break;
  case "INCL":
    op="|=";
  case "EXCL":
    if(!op)op="&=~";
    s=(a1.md=='C'?1<<a1.v:"(1<<("+a1+"))");
    if(a0.md=='V')e.v=a0+op+s;
    else e.v=JS.updV(op,a0,s);
    break;
  default:
    var d=JS._fnx[id];
    if(d){e.v=d.replace(/#/g,a0);return true}
    return false
  }
  return true
}
//
//runtime functions
function _vp(a,i){return function($){return $?a[i]=$:a[i]}}
//function _ext(t,b){t.prototype=new b();t.constructor=t}
function _ext(t,b,v){
 if(v){t.prototype=new b()/*;t.constructor=t*/}
 else {v=b;b=null}
 t._v=(b?b._v+',':"")+v;
 t._cp=_cp;
 t.prototype._cp=function(f){return t._cp(this,f)}
}
function _cp(p,q)
{
  var v=this._v,s="";
  var a=v.split(',');
  for(var i=0;i<a.length;++i){
    var k=a[i],c=k.charAt(0);
    if(c=='#'){k=k.substr(1);s+="p."+k+"._cp(q."+k+");"}
    else if(c>='1'&c<='9'){k=k.substr(1);s+="_cpa(p."+k+",q."+k+","+c+");"}
    else s+="p."+k+"=q."+k+";";
  }
  this._cp=new Function("p","q",s+"return this");
  return this._cp(p,q)
}
function _cpa(t,s,n)
{
  if(n>1){
    for(var i=0;i<t.length;++i)_cpa(t[i],s[i],n-1)
  }else if(t[0]._cp){
    for(var i=0;i<t.length;++i)t[i]._cp(s[i]);
  }else{
    for(var i=0;i<t.length;++i)t[i]=s[i];
  }
  return t
}
function _narr(v,a,b,c)
{
  var n=[];
  for(var i=0;i<a;++i)n.push(b?_narr(v,b,c):v);
  return n
}
function _arr(f,a,b,c)
{
  var n=[];
  for(var i=0;i<a;++i)n.push(b?_arr(f,b,c):f());
  return n
}
function _charr(s)
{
  var a=[];for(var i=0;i<s.length;++i)a.push(s.charAt(i));return a
}
//
function findScriptType(scp,typ)
{
  var code=[];
  for(var i=0;i<scp.length;++i){
    if(scp[i].type.toLowerCase()==typ){
      code.push(scp[i].text)
    }
  }
  return code
}

function addScript(par,code)
{
  var scp=document.createElement("script");
  scp.text=code;
  par.appendChild(scp)//this will also execute the code
}

function compileAll(typ,comp)
{
  var scp=document.getElementsByTagName("script");
  if(scp.length>0){
    var par=scp[0].parentNode;
    var code=findScriptType(scp,typ);
    for(var i=0;i<code.length;++i){
      //debLn("<pre>"+code[i]+"</pre>");
      addScript(par,comp(code[i]))
    }
  }
}
function Oberon(){}
Oberon.Init=function()
{
  Oberon.parse=new Parse(new JS());
  compileAll("text/x-oberonscript",Oberon.Compile);
}
Oberon.Compile=function(c)
{
  var p=Oberon.parse;
  p.compile(new Scan(c));
  if(p.err)debLn("<div class='err'><span>ERROR</span>: "+p.err+"</div>");
  //debLn();
  //debLn(prt(p.code()));
  return p.code()
}
function prt(js)
{
  var out=new OutStream();
  new PrettyScript(true).toHtml(new InStream(js),out);
  return out.html()
}
function $(s){return document.getElementById(s)}
function deb(s){
  var l=$('_dbg');
  if(!l){l=document.createElement("div");l.id='_dbg';document.body.appendChild(l)}
  l.innerHTML+=s
}
function debLn(s){deb((s?s:"")+"<br/>")}
function debB(c,s){deb("<span style='background-color:"+c+"'>"+s+"</span>")}
