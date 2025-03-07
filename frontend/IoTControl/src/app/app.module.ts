import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { CommonModule } from '@angular/common';
import { RouterModule } from '@angular/router';
import { HttpClientModule } from '@angular/common/http';
import { AppComponent } from './app.component';
import { AccountComponent } from './account/account.component'; // Import your component
import { routes } from './app.routes';

@NgModule({
  declarations: [
  ],
  imports: [
    AppComponent, 
    BrowserModule,
    CommonModule,
    RouterModule.forRoot(routes),
    HttpClientModule
  ],
})
export class AppModule {}
