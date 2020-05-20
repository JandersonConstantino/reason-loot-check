import React from 'react'
import { render } from 'react-dom'
import { make as App } from './components/App/App.bs'
import './index.css'

const rootElement = document.getElementById('root')

render(<App />, rootElement)
