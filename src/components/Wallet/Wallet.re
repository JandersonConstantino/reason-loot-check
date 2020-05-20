let localStorageKey = "wallet";

let getWalletValue = _ => {
  let value = Dom.Storage.(localStorage |> getItem(localStorageKey));
  let result =
    switch (value) {
    | None => 0
    | Some(value) => int_of_string(value)
    };

  result;
};

[@react.component]
let make = () => {
  let (walletBalance, setWalletBalance) = React.useState(_ => "");
  let (balance, setBalance) = React.useState(_ => "");

  let onDepositClick = _ => {
    let updatedWallet =
      string_of_int(getWalletValue() + int_of_string(balance));

    Dom.Storage.(localStorage |> setItem(localStorageKey, updatedWallet));
    setWalletBalance(_ => updatedWallet);
  };

  let onWithdrawClick = _ => {
    let updatedWallet =
      string_of_int(getWalletValue() - int_of_string(balance));

    Dom.Storage.(localStorage |> setItem(localStorageKey, updatedWallet));
    setWalletBalance(_ => updatedWallet);
  };

  let onLoad = () => {
    let currentWalletValue = getWalletValue();
    setWalletBalance(_ => string_of_int(currentWalletValue));

    None;
  };

  React.useEffect0(onLoad);

  <div>
    <h3 className="balance">
      {React.string("Wallet balance: " ++ walletBalance)}
    </h3>
    <br />
    <input
      className="input-wallet"
      value=balance
      type_="number"
      onChange=(event => {
        let value = ReactEvent.Form.target(event)##value;
        setBalance(_ => value);
      })
    />
    <button className="btn-deposit" onClick=onDepositClick>
      {React.string("Deposit")}
    </button>
    <button className="btn-withdraw" onClick=onWithdrawClick>
      {React.string("Withdraw")}
    </button>
  </div>;
};
