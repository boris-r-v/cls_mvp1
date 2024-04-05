message CreateBalance
{
    required int64                            count=1;
    required int32                            templateId=2;
    optional Decimal                          initialValue=3;
    repeated BalanceActionRule                actionRules=4;
    optional BalanceAttributes                attrs=5;
    repeated PeriodicalRecalculationFactor    recalcFactors=6;
    optional RecalculationPeriod              period=7;
    optional BalanceCreateOptions             createOptions = 8;
}


header
// nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kActionRulesFieldNumber = 4,
    kRecalcFactorsFieldNumber = 6,
    kInitialValueFieldNumber = 3,
    kAttrsFieldNumber = 5,
    kPeriodFieldNumber = 7,
    kCreateOptionsFieldNumber = 8,
    kCountFieldNumber = 1,
    kTemplateIdFieldNumber = 2,
  };
  // repeated .cls_gen.BalanceActionRule actionRules = 4;
  int actionrules_size() const;
  private:
  int _internal_actionrules_size() const;

  public:
  void clear_actionrules() ;
  ::cls_gen::BalanceActionRule* mutable_actionrules(int index);
  ::google::protobuf::RepeatedPtrField< ::cls_gen::BalanceActionRule >*  mutable_actionrules();
  private:
  const ::google::protobuf::RepeatedPtrField<::cls_gen::BalanceActionRule>& _internal_actionrules() const;
  ::google::protobuf::RepeatedPtrField<::cls_gen::BalanceActionRule>* _internal_mutable_actionrules();
  public:
  const ::cls_gen::BalanceActionRule& actionrules(int index) const;
  ::cls_gen::BalanceActionRule* add_actionrules();
  const ::google::protobuf::RepeatedPtrField< ::cls_gen::BalanceActionRule >& actionrules() const;
  
  
  // repeated .cls_gen.PeriodicalRecalculationFactor recalcFactors = 6;
  int recalcfactors_size() const;
  private:
  int _internal_recalcfactors_size() const;

  public:
  void clear_recalcfactors() ;
  ::cls_gen::PeriodicalRecalculationFactor* mutable_recalcfactors(int index);
  ::google::protobuf::RepeatedPtrField< ::cls_gen::PeriodicalRecalculationFactor >*
      mutable_recalcfactors();
  private:
  const ::google::protobuf::RepeatedPtrField<::cls_gen::PeriodicalRecalculationFactor>& _internal_recalcfactors() const;
  ::google::protobuf::RepeatedPtrField<::cls_gen::PeriodicalRecalculationFactor>* _internal_mutable_recalcfactors();
  public:
  const ::cls_gen::PeriodicalRecalculationFactor& recalcfactors(int index) const;
  ::cls_gen::PeriodicalRecalculationFactor* add_recalcfactors();
  const ::google::protobuf::RepeatedPtrField< ::cls_gen::PeriodicalRecalculationFactor >&
      recalcfactors() const;
  // optional .cls_gen.Decimal initialValue = 3;
  bool has_initialvalue() const;
  void clear_initialvalue() ;
  const ::cls_gen::Decimal& initialvalue() const;
  PROTOBUF_NODISCARD ::cls_gen::Decimal* release_initialvalue();
  ::cls_gen::Decimal* mutable_initialvalue();
  void set_allocated_initialvalue(::cls_gen::Decimal* value);
  void unsafe_arena_set_allocated_initialvalue(::cls_gen::Decimal* value);
  ::cls_gen::Decimal* unsafe_arena_release_initialvalue();

  private:
  const ::cls_gen::Decimal& _internal_initialvalue() const;
  ::cls_gen::Decimal* _internal_mutable_initialvalue();

  public:
  // optional .cls_gen.BalanceAttributes attrs = 5;
  bool has_attrs() const;
  void clear_attrs() ;
  const ::cls_gen::BalanceAttributes& attrs() const;
  PROTOBUF_NODISCARD ::cls_gen::BalanceAttributes* release_attrs();
  ::cls_gen::BalanceAttributes* mutable_attrs();
  void set_allocated_attrs(::cls_gen::BalanceAttributes* value);
  void unsafe_arena_set_allocated_attrs(::cls_gen::BalanceAttributes* value);
  ::cls_gen::BalanceAttributes* unsafe_arena_release_attrs();

  private:
  const ::cls_gen::BalanceAttributes& _internal_attrs() const;
  ::cls_gen::BalanceAttributes* _internal_mutable_attrs();

  public:
  // optional .cls_gen.RecalculationPeriod period = 7;
  bool has_period() const;
  void clear_period() ;
  const ::cls_gen::RecalculationPeriod& period() const;
  PROTOBUF_NODISCARD ::cls_gen::RecalculationPeriod* release_period();
  ::cls_gen::RecalculationPeriod* mutable_period();
  void set_allocated_period(::cls_gen::RecalculationPeriod* value);
  void unsafe_arena_set_allocated_period(::cls_gen::RecalculationPeriod* value);
  ::cls_gen::RecalculationPeriod* unsafe_arena_release_period();

  private:
  const ::cls_gen::RecalculationPeriod& _internal_period() const;
  ::cls_gen::RecalculationPeriod* _internal_mutable_period();

  public:
  // optional .cls_gen.BalanceCreateOptions createOptions = 8;
  bool has_createoptions() const;
  void clear_createoptions() ;
  const ::cls_gen::BalanceCreateOptions& createoptions() const;
  PROTOBUF_NODISCARD ::cls_gen::BalanceCreateOptions* release_createoptions();
  ::cls_gen::BalanceCreateOptions* mutable_createoptions();
  void set_allocated_createoptions(::cls_gen::BalanceCreateOptions* value);
  void unsafe_arena_set_allocated_createoptions(::cls_gen::BalanceCreateOptions* value);
  ::cls_gen::BalanceCreateOptions* unsafe_arena_release_createoptions();

  private:
  const ::cls_gen::BalanceCreateOptions& _internal_createoptions() const;
  ::cls_gen::BalanceCreateOptions* _internal_mutable_createoptions();

  public:
  // required int64 count = 1;
  bool has_count() const;
  void clear_count() ;
  ::int64_t count() const;
  void set_count(::int64_t value);

  private:
  ::int64_t _internal_count() const;
  void _internal_set_count(::int64_t value);

  public:
  // required int32 templateId = 2;
  bool has_templateid() const;
  void clear_templateid() ;
  ::int32_t templateid() const;
  void set_templateid(::int32_t value);

  private:
  ::int32_t _internal_templateid() const;
  void _internal_set_templateid(::int32_t value);

  //-----------------------------------------------------------------
message ProtocolMessage
{
    oneof message
    {
        BusinessRequest     businessRequest=1;
        BusinessResponse    businessResponse=2;
        Bind                bind=3;
        BindAck             bindAck=4;
        Unbind              unbind=5;
        UnbindAck           unbindAck=6;
        KeepAlive           keepAlive=7;
        KeepAliveAck        keepAliveAck=8;
        Pause               pause=9;
        Resume              resume=10;
    }
}
// nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kBusinessRequestFieldNumber = 1,
    kBusinessResponseFieldNumber = 2,
    kBindFieldNumber = 3,
    kBindAckFieldNumber = 4,
    kUnbindFieldNumber = 5,
    kUnbindAckFieldNumber = 6,
    kKeepAliveFieldNumber = 7,
    kKeepAliveAckFieldNumber = 8,
    kPauseFieldNumber = 9,
    kResumeFieldNumber = 10,
  };
  // .cls_gen.BusinessRequest businessRequest = 1;
  bool has_businessrequest() const;
  private:
  bool _internal_has_businessrequest() const;

  public:
  void clear_businessrequest() ;
  const ::cls_gen::BusinessRequest& businessrequest() const;
  PROTOBUF_NODISCARD ::cls_gen::BusinessRequest* release_businessrequest();
  ::cls_gen::BusinessRequest* mutable_businessrequest();
  void set_allocated_businessrequest(::cls_gen::BusinessRequest* value);
  void unsafe_arena_set_allocated_businessrequest(::cls_gen::BusinessRequest* value);
  ::cls_gen::BusinessRequest* unsafe_arena_release_businessrequest();

  private:
  const ::cls_gen::BusinessRequest& _internal_businessrequest() const;
  ::cls_gen::BusinessRequest* _internal_mutable_businessrequest();

  public:
  // .cls_gen.BusinessResponse businessResponse = 2;
  bool has_businessresponse() const;
  private:
  bool _internal_has_businessresponse() const;

  public:
  void clear_businessresponse() ;
  const ::cls_gen::BusinessResponse& businessresponse() const;
  PROTOBUF_NODISCARD ::cls_gen::BusinessResponse* release_businessresponse();
  ::cls_gen::BusinessResponse* mutable_businessresponse();
  void set_allocated_businessresponse(::cls_gen::BusinessResponse* value);
  void unsafe_arena_set_allocated_businessresponse(::cls_gen::BusinessResponse* value);
  ::cls_gen::BusinessResponse* unsafe_arena_release_businessresponse();

  private:
  const ::cls_gen::BusinessResponse& _internal_businessresponse() const;
  ::cls_gen::BusinessResponse* _internal_mutable_businessresponse();

  public:
  // .cls_gen.Bind bind = 3;
  bool has_bind() const;
  private:
  bool _internal_has_bind() const;

  public:
  void clear_bind() ;
  const ::cls_gen::Bind& bind() const;
  PROTOBUF_NODISCARD ::cls_gen::Bind* release_bind();
  ::cls_gen::Bind* mutable_bind();
  void set_allocated_bind(::cls_gen::Bind* value);
  void unsafe_arena_set_allocated_bind(::cls_gen::Bind* value);
  ::cls_gen::Bind* unsafe_arena_release_bind();

  private:
  const ::cls_gen::Bind& _internal_bind() const;
  ::cls_gen::Bind* _internal_mutable_bind();

  public:
  // .cls_gen.BindAck bindAck = 4;
  bool has_bindack() const;
  private:
  bool _internal_has_bindack() const;

  public:
  void clear_bindack() ;
  const ::cls_gen::BindAck& bindack() const;
  PROTOBUF_NODISCARD ::cls_gen::BindAck* release_bindack();
  ::cls_gen::BindAck* mutable_bindack();
  void set_allocated_bindack(::cls_gen::BindAck* value);
  void unsafe_arena_set_allocated_bindack(::cls_gen::BindAck* value);
  ::cls_gen::BindAck* unsafe_arena_release_bindack();

  private:
  const ::cls_gen::BindAck& _internal_bindack() const;
  ::cls_gen::BindAck* _internal_mutable_bindack();

  public:









message BusinessRequest
{
    required int64                   clientRequestId=1;
    required ClientContext           context=2;
    required uint32                  handlerId=3;

    oneof requestMessage
    {
        FindBalance                  findBalance=4;
        GetBalance                   getBalance=5;
        ReserveBalance               reserveBalance=6;
        SetBalance                   setBalance=7;
        CreateBalance                createBalance=8;
        SetBalanceAttribute          setBalanceAttribute=9;
        ResetBalanceAttribute        resetBalanceAttribute=10;
        DeleteBalance                deleteBalance=11;
        CommitReservation            commitReservation=12;
        RollbackReservation          rollbackReservation=13;
        RefreshBalanceTemplate       refreshBalanceTemplate=14;
        GetBalanceTemplate           getBalanceTemplate=15;
        GetActionData                getActionData=16;
        ExportBalances               exportBalances=17;
        GetBalanceTemplateList       getBalanceTemplateList=18;
        GetReservation               getReservation=19;
        SetNotificationCallback      setNotificationCallback=20;
        RecalculateBalanceProfile    recalculateBalanceProfile=24;
        BackgroundProcessTasksJob    backgroundProcessTasks=22;
        bytes                        rawData=23;
    }

    optional uint32                  commandTimeout=25;
}



  message BusinessResponse
{
    required int64                  clientRequestId=2;
    optional string                 traceId=3;
    required RequestStatus          result = 4;
    optional RequestDetailStatus    resultDetail = 5;
    repeated ResultInfo             resultInfo= 6;
    optional DebugInfo              debugInfo=7;
    optional bytes                  rawData=8;
}