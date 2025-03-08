import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { RouterModule } from '@angular/router';  
import { AppComponent } from './app.component';
import { AccountComponent } from './account/account.component';
import { CommonModule } from '@angular/common'; 

import { routes } from './app.routes'; 

@NgModule({
  declarations: [
    AppComponent,
    AccountComponent
  ],
  imports: [
    BrowserModule,
    CommonModule, 
    RouterModule.forRoot(routes)  
  ],
  providers: [],
  bootstrap: [AppComponent] 
})
export class AppModule { }
